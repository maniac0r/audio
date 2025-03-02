#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <fuzzy.h> // Use libfuzzy for fuzzy matching
#include <fstrcmp.h> // Use fstrcmp for fuzzy matching
#include <ctype.h>

#define FUZZY_THRESHOLD 0.8 // Adjusted for proper fuzzy comparison
#define MAX_ARTISTS 1000
#define MAX_RELEASES 1000

char *fav_artists[MAX_ARTISTS];
int fav_count = 0;
bool debug_mode = false;

void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void load_favorites(const char *filename) {
    if (debug_mode) printf("Loading favorite artists from file: %s\n", filename);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening favorites file");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) && fav_count < MAX_ARTISTS) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline
        trim_whitespace(buffer);
        fav_artists[fav_count++] = strdup(buffer);
        if (debug_mode) printf("Loaded favorite artist: '%s'\n", buffer);
    }
    fclose(file);
}

bool is_favorite(const char *artist) {
    trim_whitespace((char *)artist);
    for (int i = 0; i < fav_count; i++) {
        double score = fstrcasecmp(artist, fav_artists[i]);
        if (debug_mode) fprintf(stderr, "Comparing '%s' with '%s' -> Score: %f\n", artist, fav_artists[i], score);
        if (score >= FUZZY_THRESHOLD) {
            printf("<tr><td>match:'%s', score %.2f</td>", fav_artists[i], score);
            if (debug_mode) fprintf(stderr, "Match found: %s\n", artist);
            return true;
        }
        if (debug_mode) fprintf(stderr, "Not matched: %s\n", artist);
    }
    return false;
}

void parse_xml(const char *filename) {
    if (debug_mode) printf("Parsing XML file: %s\n", filename);
    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (!doc) {
        fprintf(stderr, "Failed to parse XML file\n");
        return;
    }
    xmlNode *root = xmlDocGetRootElement(doc);
    xmlNode *channel = root->children;
    while (channel && (channel->type != XML_ELEMENT_NODE || strcmp((char *)channel->name, "channel") != 0)) {
        channel = channel->next;
    }
    if (!channel) {
        fprintf(stderr, "No <channel> node found\n");
        xmlFreeDoc(doc);
        return;
    }
    for (xmlNode *node = channel->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE && strcmp((char *)node->name, "item") == 0) {
            char *title = NULL, *link = NULL, *desc = NULL, *date = NULL;
            for (xmlNode *child = node->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "title") == 0) {
                        title = strdup(content);
                    } else if (strcmp((char *)child->name, "link") == 0) {
                        link = strdup(content);
                    } else if (strcmp((char *)child->name, "description") == 0) {
                        desc = strdup(content);
                    } else if (strcmp((char *)child->name, "pubDate") == 0) {
                        date = strdup(content);
                    }
                    xmlFree(content);
                }
            }
            if (title) {
                char *artist = strdup(title);
                char *dash = strchr(artist, '-');
                if (dash) *dash = '\0'; // Extract artist name
                trim_whitespace(artist);
                if (is_favorite(artist)) {
                    printf("<td><a href=\"%s\">%s</a></td><td>%s</td><td>%s</td></tr>\n", link ? link : "N/A", title, desc ? desc : "N/A", date ? date : "N/A");
                }
                free(artist);
            }
            free(title);
            free(link);
            free(desc);
            free(date);
        }
    }
    xmlFreeDoc(doc);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <xml_file> <fav_artists_file> [-d]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 4 && strcmp(argv[3], "-d") == 0) {
        debug_mode = true;
    }
    
    load_favorites(argv[2]);
    printf("<html>\n<table border=1>\n");
    parse_xml(argv[1]);
    
    for (int i = 0; i < fav_count; i++) {
        free(fav_artists[i]);
    }
    printf("</table>\n</html>\n");
    return EXIT_SUCCESS;
}

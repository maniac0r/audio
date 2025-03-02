This is tool to watch for new vinyl releases of your favourite Artists.
It is based on the feed from [upcomingvinyl.com](https://upcomingvinyl.com/).
Provides HTML output which can be sent via email in case there was new match found (yippee!) .

```
HOW-TO:
0. Read install-prereqs file and install required libraries/tools as suggested.
1. Edit list of your favourite artists in file filter_music-artists.txt
2. Run compile.sh to get binary "fuzzy_match" for your system (included one is 64bit ARM raspi-os11)
    (before compiling you can adjust sensitivity for fuzzy-match by editing variable FUZZY_THRESHOLD which is set to 80% by default)
3. Edit your email address at the end of cron-fuzzy file
4. Schedule running cron script, for example every day 18:30 entry will look like: 30 18 * * * ~/cron-fuzzy
```

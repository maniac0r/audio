This is tool to watch for new vinyl releases of your favourite Artists.

Provides HTML output which can be sent via email in case there was new match found (yippee!) .

```
HOW-TO:
1. Edit list of your favourite artists in file filter_music-artists.txt
2. Run compile.sh to get binary "fuzzy_match" for your system (included one is 64bit ARM raspi-os11)
3. Edit your email address at the end of cron-fuzzy file
4. Schedule running cron script, for example every day 18:30 entry will look like: 30 18 * * * ~/cron-fuzzy
```

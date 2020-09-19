To get such nice looking [dashboard](Roonserver_Kibana_Dashboard.png) in Kibana , the following is required:

* [filebeat-roonserver.yml](filebeat-roonserver.yml) -> filebeat configuration (running on the same host as RoonServer, usually in /etc/filebat/filebeat.yml)
* [kibana-artifacts.ndjson](kibana-artifacts.ndjson) -> exported search, visualizations and dashboard for RoonServer logs - you need to import into Kibana
* [logstash-roonserver.conf](logstash-roonserver.conf) -> roon parsing configuration for logstash , usualy located in /etc/logstash/conf.d/roonserver.conf

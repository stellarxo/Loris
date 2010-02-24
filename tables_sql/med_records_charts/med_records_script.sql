use nihaceProd;

CREATE TABLE weight_for_age_chart (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/weight_for_age_chart.csv" into table weight_for_age_chart fields terminated by "," lines terminated by "\n";

CREATE TABLE height_for_age_chart (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/height_for_age_chart.csv" into table height_for_age_chart fields terminated by "," lines terminated by "\n";;


CREATE TABLE headcirc_for_age_chart (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/headcirc_for_age_chart.csv" into table headcirc_for_age_chart fields terminated by "," lines terminated by "\n";

CREATE TABLE weight_for_age_chart_over_2 (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/weight_for_age_chart_over_2.csv" into table weight_for_age_chart_over_2 fields terminated by "," lines terminated by "\n"; 

CREATE TABLE height_for_age_chart_over_2 (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/height_for_age_chart_over_2.csv" into table height_for_age_chart_over_2 fields terminated by "," lines terminated by "\n";;

CREATE TABLE bmi_for_age_chart_over_2 (
id INT NOT NULL, 
PRIMARY KEY(id),
Sex	INT,
Age FLOAT(4,1),	L FLOAT(10,7), M FLOAT(10,7), S FLOAT(10,7), P3 FLOAT(10,7), P5 FLOAT(10,7), P10 FLOAT(10,7), P25 FLOAT(10,7),
P50 FLOAT(10,7), P75 FLOAT(10,7), P85 FLOAT(10, 7), P90 FLOAT(10,7), P95 FLOAT(10,7), P97 FLOAT(10,7)
);

load data local infile "/export-01/nihace/www/neurodb/project/tables_sql/med_records_charts/bmi_for_age_chart_over_2.csv" into table bmi_for_age_chart_over_2 fields terminated by "," lines terminated by "\n";;



alter table head_measurements_proband change head_cirfumference1 head_circumference1  varchar(255);
alter table head_measurements_proband change head_cirfumference2 head_circumference2  varchar(255);
alter table head_measurements_proband change head_cirfumference1_status head_circumference1_status enum('not_answered');
alter table head_measurements_proband change head_cirfumference2_status head_circumference2_status enum('not_answered');

alter table head_measurements_subject change head_cirfumference1 head_circumference1  varchar(255);
alter table head_measurements_subject change head_cirfumference2 head_circumference2  varchar(255);
alter table head_measurements_subject change head_cirfumference1_status head_circumference1_status enum('not_answered');
alter table head_measurements_subject change head_cirfumference2_status head_circumference2_status enum('not_answered');

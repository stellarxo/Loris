CREATE TABLE `project_rel` (
  `ProjectID` int(2) DEFAULT NULL,
  `SubprojectID` int(2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `project_rel` VALUES (1,1),(1,2),(1,3),(1,7),(2,9),(2,10),(3,4),(3,5),(3,7),(4,6);

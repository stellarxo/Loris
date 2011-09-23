DROP TABLE IF EXISTS examiners;

CREATE TABLE `examiners` (
  `examinerID` int(10) unsigned NOT NULL auto_increment,
  `full_name` varchar(255) default NULL,
  `centerID` tinyint(2) default NULL,
  PRIMARY KEY  (`examinerID`),
  UNIQUE KEY `full_name` (`full_name`,`centerID`)
);

INSERT INTO `examiners` VALUES 
(1,'Joe Piven',1),
(2,'Alan Evans',1),
(3,'Annette Estes',2),
(4,'Vanessa Hus',2),
(5,'Vanessa Rivera',2),
(6,'Erin Kipple',2),
(7,'Lindsey Sterling',2),
(8,'Karen Burner',2),
(9,'Lauren Elder',2),
(10,'Chad Chappell',5),
(11,'Bob McKinstry',4),
(12,'Nancy Garrett',5),
(13,'Jaclyn Anthony',5),
(14,'Lisa Flake',4),
(15,'Casey Babb',4),
(16,'Kelly Botteron',4),
(17,'Sarah Patterson',3);

Deb Dunn
Isabelle Rostain
Sarah Paterson
Sarah Woldoff
Christine Ghilain
Erin Bogue
Juhi Pandey
Joanna Bisgaier
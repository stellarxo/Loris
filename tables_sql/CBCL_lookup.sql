-- MySQL dump 10.13  Distrib 5.5.28, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: ibis
-- ------------------------------------------------------
-- Server version	5.5.28-0ubuntu0.12.04.3

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CBCL_lookup`
--

DROP TABLE IF EXISTS `CBCL_lookup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CBCL_lookup` (
  `Raw` int(3) DEFAULT NULL,
  `T` int(3) DEFAULT NULL,
  `Type` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CBCL_lookup`
--

LOCK TABLES `CBCL_lookup` WRITE;
/*!40000 ALTER TABLE `CBCL_lookup` DISABLE KEYS */;
INSERT INTO `CBCL_lookup` VALUES (72,100,'Internal'),(70,99,'Internal'),(71,99,'Internal'),(69,98,'Internal'),(67,97,'Internal'),(68,97,'Internal'),(66,96,'Internal'),(64,95,'Internal'),(65,95,'Internal'),(62,94,'Internal'),(63,94,'Internal'),(61,93,'Internal'),(59,92,'Internal'),(60,92,'Internal'),(58,91,'Internal'),(56,90,'Internal'),(57,90,'Internal'),(55,89,'Internal'),(53,88,'Internal'),(54,88,'Internal'),(52,87,'Internal'),(50,86,'Internal'),(51,86,'Internal'),(48,85,'Internal'),(49,85,'Internal'),(47,84,'Internal'),(45,83,'Internal'),(46,83,'Internal'),(44,82,'Internal'),(42,81,'Internal'),(43,81,'Internal'),(40,80,'Internal'),(41,80,'Internal'),(39,79,'Internal'),(37,78,'Internal'),(38,78,'Internal'),(36,77,'Internal'),(34,76,'Internal'),(35,76,'Internal'),(33,75,'Internal'),(31,74,'Internal'),(32,74,'Internal'),(29,73,'Internal'),(30,73,'Internal'),(28,72,'Internal'),(26,71,'Internal'),(27,71,'Internal'),(25,70,'Internal'),(24,69,'Internal'),(23,68,'Internal'),(22,67,'Internal'),(21,66,'Internal'),(19,65,'Internal'),(20,65,'Internal'),(18,64,'Internal'),(17,63,'Internal'),(16,62,'Internal'),(15,61,'Internal'),(14,60,'Internal'),(13,59,'Internal'),(12,58,'Internal'),(11,56,'Internal'),(10,55,'Internal'),(9,53,'Internal'),(8,51,'Internal'),(7,49,'Internal'),(6,47,'Internal'),(5,45,'Internal'),(4,43,'Internal'),(3,41,'Internal'),(2,37,'Internal'),(1,33,'Internal'),(0,29,'Internal'),(200,100,'Total'),(199,100,'Total'),(198,100,'Total'),(197,100,'Total'),(196,99,'Total'),(195,99,'Total'),(194,99,'Total'),(193,99,'Total'),(192,99,'Total'),(191,99,'Total'),(190,98,'Total'),(189,98,'Total'),(188,98,'Total'),(187,98,'Total'),(186,98,'Total'),(185,98,'Total'),(184,97,'Total'),(183,97,'Total'),(182,97,'Total'),(181,97,'Total'),(180,97,'Total'),(179,97,'Total'),(178,96,'Total'),(177,96,'Total'),(176,96,'Total'),(175,96,'Total'),(174,96,'Total'),(173,96,'Total'),(172,96,'Total'),(171,95,'Total'),(170,95,'Total'),(169,95,'Total'),(168,95,'Total'),(167,95,'Total'),(166,95,'Total'),(165,94,'Total'),(164,94,'Total'),(163,94,'Total'),(162,94,'Total'),(161,94,'Total'),(160,94,'Total'),(159,93,'Total'),(158,93,'Total'),(157,93,'Total'),(156,93,'Total'),(155,93,'Total'),(154,93,'Total'),(153,93,'Total'),(152,92,'Total'),(151,92,'Total'),(150,92,'Total'),(149,92,'Total'),(148,92,'Total'),(147,92,'Total'),(146,91,'Total'),(145,91,'Total'),(144,91,'Total'),(143,91,'Total'),(142,92,'Total'),(141,92,'Total'),(140,90,'Total'),(139,90,'Total'),(138,90,'Total'),(137,90,'Total'),(136,90,'Total'),(135,90,'Total'),(134,89,'Total'),(133,89,'Total'),(132,89,'Total'),(131,89,'Total'),(130,89,'Total'),(129,88,'Total'),(128,88,'Total'),(128,88,'Total'),(127,88,'Total'),(126,87,'Total'),(125,87,'Total'),(124,86,'Total'),(123,86,'Total'),(122,86,'Total'),(121,85,'Total'),(120,85,'Total'),(119,85,'Total'),(118,84,'Total'),(117,84,'Total'),(116,83,'Total'),(115,83,'Total'),(114,83,'Total'),(113,82,'Total'),(112,82,'Total'),(111,82,'Total'),(110,81,'Total'),(109,81,'Total'),(108,80,'Total'),(107,80,'Total'),(106,80,'Total'),(105,79,'Total'),(104,79,'Total'),(103,79,'Total'),(102,78,'Total'),(101,78,'Total'),(100,77,'Total'),(99,77,'Total'),(98,77,'Total'),(97,76,'Total'),(96,76,'Total'),(95,76,'Total'),(94,73,'Total'),(93,73,'Total'),(92,74,'Total'),(91,74,'Total'),(90,74,'Total'),(89,73,'Total'),(88,73,'Total'),(87,73,'Total'),(86,72,'Total'),(85,72,'Total'),(84,71,'Total'),(83,71,'Total'),(82,71,'Total'),(81,70,'Total'),(79,70,'Total'),(78,70,'Total'),(77,69,'Total'),(76,69,'Total'),(75,69,'Total'),(74,68,'Total'),(73,68,'Total'),(72,68,'Total'),(71,68,'Total'),(70,68,'Total'),(69,67,'Total'),(68,67,'Total'),(67,66,'Total'),(66,66,'Total'),(65,65,'Total'),(64,65,'Total'),(63,65,'Total'),(62,65,'Total'),(63,65,'Total'),(62,64,'Total'),(61,64,'Total'),(60,63,'Total'),(59,63,'Total'),(58,63,'Total'),(57,62,'Total'),(56,62,'Total'),(55,61,'Total'),(54,61,'Total'),(53,60,'Total'),(52,60,'Total'),(51,59,'Total'),(50,59,'Total'),(49,59,'Total'),(48,59,'Total'),(47,58,'Total'),(46,58,'Total'),(45,58,'Total'),(44,57,'Total'),(43,57,'Total'),(42,56,'Total'),(41,56,'Total'),(40,55,'Total'),(39,54,'Total'),(38,54,'Total'),(37,53,'Total'),(36,53,'Total'),(35,52,'Total'),(34,52,'Total'),(33,51,'Total'),(32,51,'Total'),(31,50,'Total'),(30,50,'Total'),(29,49,'Total'),(28,48,'Total'),(27,48,'Total'),(26,47,'Total'),(25,46,'Total'),(24,46,'Total'),(23,45,'Total'),(22,45,'Total'),(21,44,'Total'),(20,43,'Total'),(19,43,'Total'),(18,42,'Total'),(17,41,'Total'),(16,41,'Total'),(15,40,'Total'),(14,40,'Total'),(13,39,'Total'),(12,38,'Total'),(11,37,'Total'),(10,37,'Total'),(9,36,'Total'),(8,35,'Total'),(7,34,'Total'),(6,33,'Total'),(5,32,'Total'),(4,31,'Total'),(3,30,'Total'),(2,29,'Total'),(1,28,'Total'),(0,28,'Total'),(48,100,'External'),(47,97,'External'),(46,95,'External'),(45,92,'External'),(44,89,'External'),(43,88,'External'),(42,86,'External'),(41,85,'External'),(40,83,'External'),(39,82,'External'),(38,80,'External'),(37,79,'External'),(36,77,'External'),(35,76,'External'),(34,74,'External'),(33,73,'External'),(32,71,'External'),(31,70,'External'),(30,69,'External'),(29,68,'External'),(28,67,'External'),(27,66,'External'),(26,65,'External'),(25,64,'External'),(24,63,'External'),(23,62,'External'),(22,61,'External'),(21,60,'External'),(20,59,'External'),(19,58,'External'),(18,57,'External'),(17,56,'External'),(16,55,'External'),(15,54,'External'),(14,52,'External'),(13,51,'External'),(12,50,'External'),(11,48,'External'),(10,47,'External'),(9,46,'External'),(8,44,'External'),(7,43,'External'),(6,42,'External'),(5,40,'External'),(3,37,'External'),(2,35,'External'),(1,32,'External'),(0,28,'External');
/*!40000 ALTER TABLE `CBCL_lookup` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-05-24 16:59:13

-- MySQL dump 10.13  Distrib 5.7.13, for linux-glibc2.5 (x86_64)
--
-- Host: localhost    Database: eduapp
-- ------------------------------------------------------
-- Server version	5.7.16-0ubuntu0.16.04.1

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
-- Table structure for table `games`
--

DROP TABLE IF EXISTS `games`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `games` (
  `gameid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `userid` int(11) unsigned NOT NULL,
  `score` int(11) DEFAULT NULL,
  `level` int(11) DEFAULT NULL,
  PRIMARY KEY (`gameid`),
  UNIQUE KEY `gamesid_UNIQUE` (`gameid`),
  KEY `userIDConstraint_idx` (`userid`),
  KEY `userIDConstraint` (`userid`),
  CONSTRAINT `UIDConstraint` FOREIGN KEY (`userid`) REFERENCES `users` (`userid`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games`
--

LOCK TABLES `games` WRITE;
/*!40000 ALTER TABLE `games` DISABLE KEYS */;
INSERT INTO `games` VALUES (15,44,2420,5),(16,57,2048,42),(17,59,2048,42),(18,63,4100,3),(19,63,4100,3),(22,63,0,1),(23,63,1100,2),(24,68,200,1),(25,68,1000,2),(26,70,200,1),(27,70,500,1),(28,70,12000,3),(29,70,12000,3);
/*!40000 ALTER TABLE `games` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `userid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(45) DEFAULT NULL,
  `password` varchar(45) DEFAULT NULL,
  `realname` varchar(45) DEFAULT NULL,
  `isteacher` varchar(45) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `classcode` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`userid`),
  UNIQUE KEY `userID_UNIQUE` (`userid`),
  UNIQUE KEY `nickname_UNIQUE` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=71 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (2,'momo','bad pass','Monish Gupta','0','LOLSCHOOL'),(3,'momoTheLoser','bad pass','Monish Gupta','0','LOLSCHOOL'),(4,'momo123','bad pass','Monish','0','CX87'),(6,'momo1234','bad pass','Monish','0','CX87'),(8,'momo12345','bad pass','Monish','0','CX87'),(9,'momo123435','bad pass','Monish','0','CX87'),(10,'momo1234356','bad pass','Monish','0','CX87'),(11,'asd','ssss','bad Name','0','nope'),(12,'noob1','1234','JohnnyJohnson','0','idk'),(13,'noob2','1234','JohnnyJohnson','0','idk'),(15,'noob3','1234','JohnnyJohnson','0','idk'),(17,'noob4','1234','JohnnyJohnson','0','idk'),(18,'noob5','1234','JohnnyJohnson','0','idk'),(19,'noob6','1234','JohnnyJohnson','0','idk'),(20,'noob7','1234','JohnnyJohnson','0','idk'),(21,'noob8','1234','JohnnyJohnson','1','idk'),(22,'noob9','1234','JohnnyJohnson','1','idk'),(23,'noob10','1234','JohnnyJohnson','1','idk'),(24,'noob13','1234','JohnnyJohnson','1','idk'),(25,'noob14','1234','JohnnyJohnson','1','idk'),(26,'noob15','1234','JohnnyJohnson','1','idk'),(27,'noob16','1234','JohnnyJohnson','1','idk'),(28,'noob17','1234','JohnnyJohnson','1','idk'),(29,'noob18','1234','JohnnyJohnson','1','idk'),(30,'noob19','1234','JohnnyJohnson','1','idk'),(31,'noob20','1234','JohnnyJohnson','1','idk'),(34,'noob22','1234','JohnnyJohnson','1','idk'),(35,'noob21','1234','JohnnyJohnson','1','idk'),(41,'noob25','1234','JohnnyJohnson','1','idk'),(43,'[asdas, asdasdasd]','1234','JohnnyJohnson','1','idk'),(44,'[idk, dksk]','1234','JohnnyJohnson','1','idk'),(57,'[idk1, dksk]','1234','JohnnyJohnson','1','idk'),(59,'[idk2, dksk]','1234','JohnnyJohnson','1','idk'),(60,'mac','mac','Mac','1','N/A'),(61,'mckay','mckayf','McKay','1','N/A'),(63,'mckayf','mckay','McKay','1','N/A'),(64,'new','new','new','1','N/A'),(65,'mckayteach','mckay','McKay','0','456'),(67,'mckayTeacher','mckay','McKay Teacher','1','911'),(68,'mckayStudent','mckay','McKay Student','0','911'),(69,'mckayTeacher2','mckay','McKay Teacher2','1','4736'),(70,'mckayStudent2','mckay','McKay Student2','0','4736');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-10 21:30:31

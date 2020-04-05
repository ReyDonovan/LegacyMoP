DROP TABLE IF EXISTS `realm_classes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `realm_classes` (
  `realmId` int(11) NOT NULL,
  `class` tinyint(4) NOT NULL COMMENT 'Class Id',
  `expansion` tinyint(4) NOT NULL COMMENT 'Expansion for class activation',
  PRIMARY KEY (`realmId`,`class`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `realm_classes`
--

LOCK TABLES `realm_classes` WRITE;
/*!40000 ALTER TABLE `realm_classes` DISABLE KEYS */;
INSERT INTO `realm_classes` VALUES (1,1,0),(1,2,0),(1,3,0),(1,4,0),(1,5,0),(1,6,2),(1,7,0),(1,8,0),(1,9,0),(1,10,4),(1,11,0);
/*!40000 ALTER TABLE `realm_classes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `realm_races`
--

DROP TABLE IF EXISTS `realm_races`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `realm_races` (
  `realmId` int(11) NOT NULL,
  `race` tinyint(4) NOT NULL COMMENT 'Race Id',
  `expansion` tinyint(4) NOT NULL COMMENT 'Expansion for race activation',
  PRIMARY KEY (`realmId`,`race`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `realm_races`
--

LOCK TABLES `realm_races` WRITE;
/*!40000 ALTER TABLE `realm_races` DISABLE KEYS */;
INSERT INTO `realm_races` VALUES (1,1,0),(1,2,0),(1,3,0),(1,4,0),(1,5,0),(1,6,0),(1,7,0),(1,8,0),(1,9,3),(1,10,1),(1,11,1),(1,22,3),(1,24,4),(1,25,4),(1,26,4);
/*!40000 ALTER TABLE `realm_races` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `realmcharacters`
--

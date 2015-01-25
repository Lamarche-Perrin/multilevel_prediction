
suppressDuplicates("DATA")
suppressDuplicates("DATA",TRUE)



setwd("C:/Users/Robin/Mes projets/programming/multilevel_prediction/data")
data <- read.csv("DATA_FORMATED.CSV", sep = ",")
data <- data[!data$PREM %in% c("MACRO_2B","MACRO_3B","MACRO_4B","MACRO_5B","AGENT1_2B","AGENT1_3B","AGENT1_4B","AGENT1_5B","AGENT1_MACRO_2B","AGENT1_MACRO_3B","AGENT1_MACRO_4B","AGENT1_MACRO_5B"),]
write.csv(data,file="DATA_FORMATED.CSV",row.names=FALSE)


suppressDuplicates <- function (file, force = FALSE) {
  
  setwd("C:/Users/Robin/Mes projets/programming/multilevel_prediction/data")
  
  data <- rbind(read.csv(paste(file,".CSV",sep=""), sep = ","), read.csv(paste(file,"_FORMATED.CSV",sep=""), sep = ","))
  
  duplicates <- duplicated(data)
  
  realDuplicates <- duplicated(data[,c("TYPE","UPDATE","SIZE1","SIZE2","INTRARATE1","INTRARATE2","INTERRATE1","INTERRATE2","CONTRARIAN1","CONTRARIAN2","PREM","POSTM","TIME","DELAY")])
  
  if (all(duplicates == realDuplicates)) {
    data <- unique(data)
    
    data <- data[with(data, order(data$TYPE, data$UPDATE, data$SIZE1, data$SIZE2, data$INTRARATE1, data$INTRARATE2, data$INTERRATE1, data$INTERRATE2, data$CONTRARIAN1, data$CONTRARIAN2, data$TIME, data$DELAY, data$POSTM, data$PREM)), ]
    
    write.csv(data,file=paste(file,"_FORMATED.CSV",sep=""),row.names=FALSE)
    write.csv(data[c(),],file=paste(file,".CSV",sep=""),row.names=FALSE)
    print("DONE!")
  } else {
    print ("ERROR!")
    
    if (force) {
      data <- rbind(read.csv(paste(file,".CSV",sep=""), sep = ","), read.csv(paste(file,"_FORMATED.CSV",sep=""), sep = ","))
      
      duplicates <- duplicated(data[,c("TYPE","UPDATE","SIZE1","SIZE2","INTRARATE1","INTRARATE2","INTERRATE1","INTERRATE2","CONTRARIAN1","CONTRARIAN2","PREM","POSTM","TIME","DELAY")])
      
      data <- data[!duplicates,]
      data <- data[with(data, order(data$TYPE, data$UPDATE, data$SIZE1, data$SIZE2, data$INTRARATE1, data$INTRARATE2, data$INTERRATE1, data$INTERRATE2, data$CONTRARIAN1, data$CONTRARIAN2, data$TIME, data$DELAY, data$POSTM, data$PREM)), ]
      
      write.csv(data,file=paste(file,"_FORMATED.CSV",sep=""),row.names=FALSE)
      write.csv(data[c(),],file=paste(file,".CSV",sep=""),row.names=FALSE)
      print("DONE!")
    }
  }
}

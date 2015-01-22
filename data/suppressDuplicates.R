
suppressDuplicates("DATA")
suppressDuplicates("DATA",TRUE)


suppressDuplicates <- function (file, force = FALSE) {
  
  setwd("C:/Users/Robin/Mes projets/programming/aggregation_algorithms/aggregation/full_aggregation/data/VoterModel")
  
  data <- rbind(read.csv(paste(file,".CSV",sep=""), sep = ","), read.csv(paste(file,"_FORMATED.CSV",sep=""), sep = ","))
  
  duplicates <- duplicated(data)
  
  realDuplicates <- duplicated(data[,c("TYPE","UPDATE","SIZE1","SIZE2","INTRARATE1","INTRARATE2","INTERRATE1","INTERRATE2","CONTRARIAN","PREM","POSTM","TIME","DELAY")])
  
  if (all(duplicates == realDuplicates)) {
    data <- unique(data)
    
    data <- data[with(data, order(data$TYPE, data$UPDATE, data$SIZE1, data$SIZE2, data$INTRARATE1, data$INTRARATE2, data$INTERRATE1, data$INTERRATE2, data$CONTRARIAN, data$TIME, data$DELAY, data$POSTM, data$PREM)), ]
    
    write.csv(data,file=paste(file,"_FORMATED.CSV",sep=""),row.names=FALSE)
    write.csv(data[c(),],file=paste(file,".CSV",sep=""),row.names=FALSE)
    print("DONE!")
  } else {
    print ("ERROR!")
    
    if (force) {
      data <- rbind(read.csv(paste(file,".CSV",sep=""), sep = ","), read.csv(paste(file,"_FORMATED.CSV",sep=""), sep = ","))
      
      duplicates <- duplicated(data[,c("TYPE","UPDATE","SIZE1","SIZE2","INTRARATE1","INTRARATE2","INTERRATE1","INTERRATE2","CONTRARIAN","PREM","POSTM","TIME","DELAY")])
      
      data <- data[!duplicates,]
      data <- data[with(data, order(data$TYPE, data$UPDATE, data$SIZE1, data$SIZE2, data$INTRARATE1, data$INTRARATE2, data$INTERRATE1, data$INTERRATE2, data$CONTRARIAN, data$PREM, data$POSTM, data$TIME, data$DELAY)), ]
      
      write.csv(data,file=paste(file,"_FORMATED.CSV",sep=""),row.names=FALSE)
      write.csv(data[c(),],file=paste(file,".CSV",sep=""),row.names=FALSE)
      print("DONE!")
    }
  }
}

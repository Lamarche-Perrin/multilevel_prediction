
preMeasurement <- c("EMPTY","MICRO_MS","AGENT1_MS","MESO1_MS","MESO2_MS","MACRO_MS",
                   "AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MESO2_MS","AGENT1_MESO1_MESO2_MS")

postMeasurement <- "AGENT1_MS"

poset <- list(c("EMPTY","AGENT1_MS"), c("EMPTY","MESO1_MS"), c("EMPTY","MESO2_MS"), c("EMPTY","MACRO_MS"),
             c("AGENT1_MS","AGENT1_MESO1_MS"), c("AGENT1_MS","AGENT1_MESO2_MS"), c("AGENT1_MS","AGENT1_MACRO_MS"),
             c("MESO1_MS","AGENT1_MESO1_MS"), c("MESO1_MS","MESO1_MESO2_MS"),
             c("MESO2_MS","AGENT1_MESO2_MS"), c("MESO2_MS","MESO1_MESO2_MS"),
             c("MACRO_MS","AGENT1_MACRO_MS"), c("MACRO_MS","MESO1_MESO2_MS"),
             c("AGENT1_MESO1_MS", "AGENT1_MESO1_MESO2_MS"), c("AGENT1_MESO2_MS", "AGENT1_MESO1_MESO2_MS"),
             c("AGENT1_MACRO_MS", "AGENT1_MESO1_MESO2_MS"), c("MESO1_MESO2_MS", "AGENT1_MESO1_MESO2_MS"),
             c("AGENT1_MESO1_MESO2_MS", "MICRO_MS")
)

measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO2_MS" = c("AGENT","MESO2"),
  "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO1","MESO2"), "MACRO_MS" = c("MACRO"),
  "AGENT1_MACRO_MS" = c("AGENT","MACRO"), "AGENT1_MESO1_MS" = c("AGENT","MESO1"),
  "MESO1_MS" = c("MESO1"), "MESO1_MESO2_MS" = c("MESO1","MESO2"), "MESO2_MS" = c("MESO2"), "MICRO_MS" = c("MICRO")
)


getData (inputFileName = "DATA_FORMATED", outputFileName = "delay", type = "GENERAL_MODEL", update = "EDGES", var = "DELAY",
         size1 = 4, size2 = 4, intrarate1 = 1, intrarate2 = 1, interrate1 = 0.2, interrate2 = 0.2, contrarian1 = 0, contrarian2 = 0,
         time = 0, delay = seq(1,30), preMeasurement = preMeasurement, postMeasurement = postMeasurement, poset = poset)

getData (inputFileName = "DATA_FORMATED", outputFileName = "time", type = "GENERAL_MODEL", update = "EDGES", var = "TIME",
         size1 = 4, size2 = 4, intrarate1 = 1, intrarate2 = 1, interrate1 = 0.2, interrate2 = 0.2, contrarian1 = 0, contrarian2 = 0,
         time = seq(0,30), delay = 1, preMeasurement = preMeasurement, postMeasurement = postMeasurement, poset = poset)


getData <- function (type, update, var, size1, size2, intrarate1, intrarate2, interrate1, interrate2, contrarian1, contrarian2,
                     time, delay, preMeasurement, postMeasurement, poset,
                     inputFileName, outputFileName, width = 1920, height = 1080, res = 150) {

  data <- read.csv(paste("~/programming/multilevel_prediction/data/",inputFileName,".CSV",sep=""), sep = ",")
  data <- data[data$TYPE %in% type & data$UPDATE %in% update & data$SIZE1 %in% size1 & data$SIZE2 %in% size2
               & data$INTRARATE1 %in% round(intrarate1,6) & data$INTRARATE2 %in% round(intrarate2,6)
               & data$INTERRATE1 %in% round(interrate1,6) & data$INTERRATE2 %in% round(interrate2,6)
               & data$CONTRARIAN1 %in% round(contrarian1,6) & data$CONTRARIAN2 %in% round(contrarian2,6)
               & data$TIME %in% time & data$DELAY %in% delay & data$PREM %in% preMeasurement & data$POSTM %in% postMeasurement,]
  
  nb <- nrow(data)
  print(nb)
  
  xlim <- c(min(data$CURRENT_I), max(data$CURRENT_I)*1.1)
  ylim <- c(min(data$MACRO_I), max(data$MACRO_I)*1.1)
  
  vTime <- time
  vDelay <- delay

  if (var == "TIME") {
    values <- time
    vTime <- NULL
  }
  
  if (var == "DELAY") {
    values <- delay
    vDelay <- NULL
  }
  
  old.par <- par(mfrow=c(1, 2))
  plotIB (inputFileName = inputFileName, type = type, update = update, modelName = "",
          phaseDiagram = TRUE, noLegend = TRUE, phasesNames = TRUE, noTitle = TRUE, noNegativeValue = TRUE,
          xAxis = var, yAxis = "BETA", yMin = 0, yMax = 200, xMin = min(values), xMax = max(values), varMin = min(values),
          suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
          postMeasurement = postMeasurement, preMeasurement = preMeasurement, measurementText = measurementText,
          print = FALSE, var = var, size = c(size1,size2), intraRate = c(intrarate1,intrarate2),
          interRate = c(interrate1,interrate2), contrarian = c(contrarian1,contrarian2), time = vTime, delay = vDelay)
  
  IBplot <- recordPlot()
  dev.off()
  
  system(paste("rm -rf ~/programming/multilevel_prediction/data/animation/",outputFileName,sep=""))
  system(paste("rm -f ~/programming/multilevel_prediction/data/animation/",outputFileName,".avi",sep=""))
  system(paste("mkdir ~/programming/multilevel_prediction/data/animation/",outputFileName,sep=""))
  
  for (v in values) {
    print(v)
    png(paste("~/programming/multilevel_prediction/data/animation/",outputFileName,"/frame_",v,".png",sep=""),
        width=width, height=height, res=res)
  
    replayPlot(IBplot)
    abline(v=v)
    
    d <- data[data[,var] == v,]
  
    threshold <- 1
    for (m1 in preMeasurement) {
      d[d$PREM == m1,"OPTIMAL"] <- TRUE
      for (m2 in preMeasurement) {
        if (m1 != m2 && d[d$PREM == m2,"CURRENT_I"]*threshold < d[d$PREM == m1,"CURRENT_I"]
            && d[d$PREM == m2,"MACRO_I"] > d[d$PREM == m1,"MACRO_I"]*threshold) { d[d$PREM == m1,"OPTIMAL"] <- FALSE }
        if (!d[d$PREM == m1,"OPTIMAL"]) break
      }
    }
    d[d$PREM == "MICRO_MS","OPTIMAL"] <- TRUE

    d$CHULL <- FALSE
    ch <- chull(c(d$CURRENT_I,min(d$CURRENT_I),max(d$CURRENT_I)),c(d$MACRO_I,-1,-1))
    for (m in d$PREM[ch]) { if (!is.na(m)) { d[d$PREM == m,"CHULL"] <- TRUE } }
    d$OPTIMAL <- d$CHULL
    
    d$PCH <- ifelse(d$OPTIMAL,19,1)
    d$FONT <- ifelse(d$OPTIMAL,2,1)
    
    
    xlim <- c(min(d$CURRENT_I), max(d$CURRENT_I)*1.1)
    ylim <- c(min(d$MACRO_I), max(d$MACRO_I)*1.1)
    par(mar=c(4,4,1,1)+.1)
    plot(d$CURRENT_I, d$MACRO_I, xlab="", ylab="", pch=d$PCH, xlim=xlim, ylim=ylim)
    
    
    #title(paste("delay = ",v,sep=""))
    title(xlab = "Complexity", line = 2.5)
    title(ylab = "Predictive Capacity", line = 2)
    
    labels <- c()
    for (m in d$PREM) {
      labels <- c(labels, paste(measurementText[[m]],collapse="\n"))
    }
    text(d$CURRENT_I, d$MACRO_I, labels=labels, cex= 0.7, pos=3, font=d$FONT)
  
    x0 <- c()
    y0 <- c()
    x1 <- c()
    y1 <- c()
    lty <- c()
    lwd <- c()
    for (i in seq(1,length(poset))) {
      c <- poset[[i]]
      x0 <- c(x0,d[d$PREM == c[1],"CURRENT_I"])
      y0 <- c(y0,d[d$PREM == c[1],"MACRO_I"])
      x1 <- c(x1,d[d$PREM == c[2],"CURRENT_I"])
      y1 <- c(y1,d[d$PREM == c[2],"MACRO_I"])
      if (d[d$PREM == c[1],"OPTIMAL"] && d[d$PREM == c[2],"OPTIMAL"]) {
        lty <- c(lty,1)
        lwd <- c(lwd,2)
      } else {
        lty <- c(lty,2)
        lwd <- c(lwd,1)
      }
    }
    segments(x0,y0,x1,y1,lty=lty,lwd=lwd)
  
    par(old.par)
    dev.off(dev.cur())
  }
  
  system(paste("avconv -r 1 -i ~/programming/multilevel_prediction/data/animation/",outputFileName,
         "/frame_%d.png ~/programming/multilevel_prediction/data/animation/",outputFileName,".avi",sep=""))

}


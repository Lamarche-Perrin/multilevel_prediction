library(RColorBrewer)

print <- FALSE
width = 6
height = 5


library(RColorBrewer)




suppressDuplicates("DATA_TWO_COMMUNITIES")
suppressDuplicates("DATA_COMPLETE")


suppressDuplicates <- function (file) {
  
  setwd("C:/Users/Robin/Mes projets/programming/aggregation_algorithms/aggregation/full_aggregation/data/VoterModel")
  
  data <- rbind(read.csv(paste(file,".CSV",sep=""), sep = ","), read.csv(paste(file,"_FORMATED.CSV",sep=""), sep = ","))
  
  duplicates <- duplicated(data)
  
  if (file == "DATA_COMPLETE") {
    realDuplicates <- duplicated(data[,c("TYPE","UPDATE","SIZE","CONTRARIAN","TIME","DELAY","PREM","POSTM")])
  }
  
  if (file == "DATA_TWO_COMMUNITIES") {
    realDuplicates <- duplicated(data[,c("TYPE","SIZE1","SIZE2","INTRARATE1","INTRARATE2","INTERRATE1","INTERRATE2","DATE1","DATE2","PREM","POSTM")])
  }
  
  
  if (all(duplicates == realDuplicates)) {
    data <- unique(data)
    
    if (file == "DATA_COMPLETE") {
      data <- data[with(data, order(data$TYPE, data$UPDATE, data$SIZE, data$CONTRARIAN, data$TIME, data$DELAY, data$PREM, data$POSTM)), ]
    }
    
    if (file == "DATA_TWO_COMMUNITIES") {
      data <- data[with(data, order(data$TYPE, data$SIZE1, data$SIZE2, data$INTRARATE1, data$INTRARATE2, data$INTERRATE1, data$INTERRATE2, data$DATE1, data$DATE2, data$PREM, data$POSTM)), ]
    }
    
    write.csv(data,file=paste(file,"_FORMATED.CSV",sep=""),row.names=FALSE)
    write.csv(data[c(),],file=paste(file,".CSV",sep=""),row.names=FALSE)
    print("DONE!")
  } else {
    print ("ERROR!")
  }
  
}


plotIB <- function (inputFileName, type, update, preMeasurement, postMeasurement, xAxis = "CURRENT_I", yAxis = "MACRO_I",
                    var, varMin = NULL, varMax = NULL, varStep = NULL, varList = NULL, beta = 1,
                    pointMin = NULL, pointMax = NULL, pointStep = NULL, pointList = NULL,
                    labelMin = NULL, labelMax = NULL, labelStep = NULL, labelList = NULL, noLabel = NULL, unicolor = FALSE,
                    size = NULL, time = NULL, delay = NULL, intraRate = NULL, interRate = NULL, contrarian = NULL,
                    xMin = NULL, xMax = NULL, yMin = NULL, yMax = NULL, noTitle = FALSE,
                    displayBinaryVariable = FALSE, displayMinXAxis = NULL, displayMaxXAxis = NULL,
                    displayMinYAxis = NULL, displayMaxYAxis = NULL, legendPos = "bottomright",
                    addText = NULL, addTextX = NULL, addTextY = NULL, noNegativeValue = FALSE,
                    position = NULL, noLegend = FALSE, phaseDiagram = FALSE, mainPhases = TRUE,
                    suppressSubPhases = FALSE, suppressInterPhases = FALSE,
                    print = FALSE, pdf = TRUE, outputFileName = NULL, width = 8, height = 6, res = 600,
                    expId = NULL) {
  
  setwd("C:/Users/Robin/Mes projets/programming/aggregation_algorithms/aggregation/full_aggregation/data/VoterModel")
  
  if (is.null(outputFileName)) { outputFileName = inputFileName }
  
  if (type == "TWO_COMMUNITIES") {
    if (is.null(size)) { size <- c(NULL,NULL) }
    if (is.null(intraRate)) { intraRate <- c(NULL,NULL) }
    if (is.null(interRate)) { interRate <- c(NULL,NULL) }
    
    size1 <- size[1]
    size2 <- size[2]
    intraRate1 <- intraRate[1]
    intraRate2 <- intraRate[2]
    interRate1 <- interRate[1]
    interRate2 <- interRate[2]
  }
  
  c <- brewer.pal(9,"Set1")
  
  color <- list("MACRO_MS" = c[2], "MICRO_MS" = c[1], "EMPTY_MS" = c[9], "AGENT_MS" = c[3], "MACRO_AND_AGENT" = c[4],
                "MESO1_MS" = c[5], "MESO2_MS" = c[6], "MESO_MS" = c[7], "MESO_AND_AGENT" = "black",
                "MACRO_AND_MESO" = c[7], "MACRO_MESO_AND_AGENT" = c[8])
  
  measurementLabel <- list("MACRO_MS" = "Macroscopic measurement", "MICRO_MS" = "Microscopic measurement",
                           "EMPTY" = "Empty measurement", "AGENT_MS" = "One-agent measurement",
                           "MACRO_AND_AGENT" = "Multilevel measurement", "MESO1" = "Mesoscopic", "MESO_AND_AGENT" = "Agent and Meso",
                           "MESO2" = "Mesoscopic 2", "MESO" = "Two-mesoscopic", "MACRO_AND_MESO" = "Meso and Macro",
                           "MACRO_MESO_AND_AGENT" = "Agent, Meso and Macro",
                           "BETA_MACRO_EMPTY" = "IB-empty = IB-macro", "BETA_EMPTY_MACRO" = "IB-empty = IB-macro",
                           "BETA_MACRO_AGENT" = "IB-agent = IB-macro", "BETA_AGENT_MACRO" = "IB-agent = IB-macro",
                           "BETA_EMPTY_AGENT" = "IB-empty = IB-agent", "BETA_AGENT_EMPTY" = "IB-empty = IB-agent",
                           "BETA_EMPTY_MACRO_AND_AGENT" = "IB-empty = IB-multilevel",
                           "BETA_EMPTY_MACRO_AND_AGENT" = "IB-empty = IB-multilevel",
                           "BETA_AGENT_MACRO_AND_AGENT" = "IB-agent = IB-multilevel",
                           "BETA_MACRO_AND_AGENT_AGENT" = "IB-agent = IB-multilevel",
                           "BETA_MACRO_MACRO_AND_AGENT" = "IB-macro = IB-multilevel",
                           "BETA_MACRO_AND_AGENT_MACRO" = "IB-macro = IB-multilevel"
  )
  
  # MAKE TITLE AND SUBTITLE
  title <- ""
  subtitle <- ""
  legendtitle <- ""
  
  postMTxt <- bquote(Phi)
  
  if (postMeasurement == "MACRO_MS") {
    title <- bquote("Predicting the " ~ bold("Macroscopic Measurement"))
    postMTxt <- bquote(phi[T])
  }
  
  if (postMeasurement == "MICRO_MS") {
    title <- bquote("Predicting the " ~ bold("Microscopic Measurement"))
  }
  
  if (postMeasurement == "AGENT_MS") {
    title <- bquote("Predicting a " ~ bold("One-agent Measurement"))
    postMTxt <- bquote(phi[group("{",omega,"}")])
  }
  
  if (type == "COMPLETE") { title <- bquote(.(title) ~ " of the " ~ bold("Complete Voter Graph")) }
  if (type == "TWO_COMMUNITIES") { title <- bquote(.(title) ~ " of " ~ bold("Two Communities")) }  
  
  timeTxt <- bquote("time: " ~ t == .(time) ~ ", ")
  delayTxt <- bquote("delay: " ~ tau == .(delay) ~ ", ")
  rateTxt <- bquote("")
  sizeTxt <- bquote("")
  
  contTxt <- bquote("")
  if (!is.null(contrarian) && contrarian > 0) { contTxt <- bquote("contrarian: " ~ c == .(contrarian) ~ ", ") }
  
  if (type == "COMPLETE") { sizeTxt <- bquote("size: " ~ group("|",X,"|") == .(size) ~ ", ") }
  
  if (type == "TWO_COMMUNITIES") {
    sizeTxt <- bquote("size: " ~ group("|",X,"|") == .(size1) + .(size2) ~ ", ")
    rateTxt <- bquote("interaction weight: " ~ omega == .(interRate1) ~ ", ")
  }
  
  if (var == "DELAY") {
    subtitle <- bquote("(" ~ .(sizeTxt) ~ .(timeTxt) ~ .(rateTxt) ~ .(contTxt)
                       ~ "and variable delay:" ~ tau %in% ~ group("[",list(0,infinity),"[") ~ ")")
    currentStateTxt <- bquote(X^.(time))
    if (time > 0) { nextStateTxt <- bquote(X^{.(time)+tau}) } else { nextStateTxt <- bquote(X^tau) }
    if (xAxis != var && yAxis != var) {
      legendtitle <- bquote("Delay " ~ tau)
      legendvalue <- 48 + 0
    }
  }  
  
  if (var == "TIME") {
    subtitle <- bquote("(" ~ .(sizeTxt) ~ .(delayTxt) ~ .(rateTxt) ~ .(contTxt)
                       ~ "and variable time:" ~ t %in% ~ group("[",list(0,infinity),"[") ~ ")")
    currentStateTxt <- bquote(X^t)
    if (delay > 0) { nextStateTxt <- bquote(X^{t+.(delay)}) } else { nextStateTxt <- bquote(X^t) }
    if (xAxis != var && yAxis != var) {
      legendtitle <- bquote("Time " ~ t)
      legendvalue <- 48 + 0
    }
  }
  
  if (var == "SIZE") {
    subtitle <- bquote("(" ~ .(timeTxt) ~ .(delayTxt) ~ .(rateTxt) ~ .(contTxt)
                       ~ "and variable size:" ~ group("|",X,"|") %in% ~ group("[",list(2,infinity),"[") ~ ")")
    currentStateTxt <- bquote(X^.(time))
    nextStateTxt <- bquote(X^.(time+delay))
    if (xAxis != var && yAxis != var) {
      legendtitle <- bquote("Size " ~ group("|",X,"|"))
      legendvalue <- 48 + 0
    }
  }
  
  
  if (var == "CONTRARIAN") {
    subtitle <- bquote("(" ~ .(sizeTxt) ~ .(timeTxt) ~ .(delayTxt) ~ .(rateTxt)
                       ~ "and variable contrarian rate:" ~ c %in% ~ group("[",list(0,1),"]") ~ ")")
    currentStateTxt <- bquote(X^.(time))
    nextStateTxt <- bquote(X^.(time+delay))
    if (xAxis != var && yAxis != var) {
      legendtitle <- bquote("Contrarian rate " ~ c)
      legendvalue <- 48 + 0
    }
  }
  
  axisLabel <- list("CURRENT_I" = bquote("Model Complexity   " ~ H ~ bgroup("(",phi ~ group("(",.(currentStateTxt),")"),")")),
                    "MACRO_I" = bquote("Anticipatory Capacity   " ~ I ~ bgroup("(",phi ~ group("(",.(currentStateTxt),")") ~ ";" ~ .(postMTxt) ~ group("(",.(nextStateTxt),")"),")")),
                    "MACRO_COND_H" = bquote("Non-predicted Complexity   " ~ H ~ bgroup("(",.(postMTxt) ~ group("(",.(nextStateTxt),")") ~ "|" ~ phi ~ group("(",.(currentStateTxt),")"),")")),
                    "TIME" = bquote("Time   " ~ t),
                    "DELAY" = bquote("Delay   " ~ tau),
                    "BETA" = bquote("Trade-off Parameter   " ~ beta),
                    "IB" = bquote("Information Bottleneck with" ~ beta == .(beta))
  )
  
  xlab <- xAxis
  ylab <- yAxis
  
  if (!is.null(axisLabel[[xAxis]])) { xlab = axisLabel[[xAxis]] }
  if (!is.null(axisLabel[[yAxis]])) { ylab = axisLabel[[yAxis]] }
  
  
  
  # READ AND FILTER DATA
  
  data <- read.csv(paste(inputFileName,".csv",sep=""), sep = ",")
  data <- data[data$TYPE == type & data$UPDATE == update & data$POSTM == postMeasurement,]
  
  if (!is.null(varMin)) { data <- data[data[,var] >= varMin,] }
  if (!is.null(varMax)) { data <- data[data[,var] <= varMax,] }
  if (!is.null(varStep)) { data <- data[data[,var] %% varStep == 0,] }        
  
  if (type == "COMPLETE") {
    if (var != "SIZE") { data <- data[data$SIZE == size,] }
  }
  
  if (type == "TWO_COMMUNITIES") {
    data <- data[data$SIZE1 == size1 & data$SIZE2 == size2 & data$INTRARATE1 == intraRate1 & data$INTRARATE2 == intraRate2 & data$INTERRATE1 == interRate1 & data$INTERRATE2 == interRate2,]
  }
  
  if (var == "TIME") {
    data <- data[data$DELAY == delay & data$CONTRARIAN == contrarian,]
    data <- data[with(data, order(data$TIME)), ]
  }
  
  if (var == "SIZE") {
    data <- data[data$TIME == time & data$DELAY == delay & data$CONTRARIAN == contrarian,]
    data <- data[with(data, order(data$SIZE)), ]
  }
  
  if (var == "DELAY") {
    data <- data[data$TIME == time & data$CONTRARIAN == contrarian,]
    data <- data[with(data, order(data$DELAY)), ]
  }
  
  if (var == "CONTRARIAN") {
    data <- data[data$TIME == time & data$DELAY == delay,]
    data <- data[with(data, order(data$CONTRARIAN)), ]
  }
  
  if (xAxis == "MACRO_COND_H" || yAxis == "MACRO_COND_H") {
    data$MACRO_COND_H <- data$NEXT_MACRO_H - data$MACRO_I
  }
  
  if (xAxis == "BETA" || yAxis == "BETA") {
    newPreMeasurement <- c()
    data <- data[,c("PREM",var,"CURRENT_I","MACRO_I")]
    data$BETA <- NA
    data$PREM_INF <- NA
    data$PREM_SUP <- NA
    
    for (i in seq(1,length(preMeasurement)-1)) {
      for (j in seq((i+1),length(preMeasurement))) {
        preM1 <- preMeasurement[i]
        preM2 <- preMeasurement[j]
        d1 <- data[data$PREM == preM1,]
        d2 <- data[data$PREM == preM2,]
        d <- merge(d1,d2,by=var)
        d$BETA <- (d$CURRENT_I.x - d$CURRENT_I.y) / (d$MACRO_I.x - d$MACRO_I.y)
        d$IB.x <- d$CURRENT_I.x - (d$BETA-1) * d$MACRO_I.x
        d$IB.y <- d$CURRENT_I.y - (d$BETA-1) * d$MACRO_I.y
        
        newPreM <- paste("BETA_",preM1,"_",preM2,sep="")
        d$PREM <- newPreM
        d$PREM_INF <- ifelse(d$IB.x > d$IB.y,preM2,preM1)
        d$PREM_SUP <- ifelse(d$IB.x > d$IB.y,preM1,preM2)
        d$CURRENT_I <- NA
        d$MACRO_I <- NA
        data <- rbind(d[,c("PREM","PREM_INF","PREM_SUP",var,"BETA","CURRENT_I","MACRO_I")],data)
        newPreMeasurement <- c(newPreMeasurement,newPreM)
        noLabel <- c(noLabel,newPreM)
      }
    }
    preMeasurement <- newPreMeasurement
    data <- data[!is.na(data$BETA),]
    data$DISPLAY <- TRUE
    
    for (r in seq(1,nrow(data))) {
      v <- data[r,var]
      beta <- data[r,"BETA"]
      prem_inf <- data[r,"PREM_INF"]
      prem_sup <- data[r,"PREM_SUP"]
      
      if (min(data[data[,var] == v & data$PREM_INF == prem_inf,"BETA"]) < beta) { data[r,"DISPLAY"] <- FALSE }
      if (max(data[data[,var] == v & data$PREM_SUP == prem_sup,"BETA"]) > beta) { data[r,"DISPLAY"] <- FALSE }
    }
    
    data <- data[data$BETA != Inf & data$BETA != -Inf,]
  }
  
  
  if (xAxis == "IB" || yAxis == "IB") { data$IB <- data$CURRENT_I - beta * data$MACRO_I }
  
  # PRINT PLOT
  
  if (nrow(data) == 0) {
    print("NO RESULT!")
  } else {
    
    if (print) {
      if (pdf) {  
        pdf(paste(outputFileName,".pdf",sep = ""), width=width, height=height, useDingbats=FALSE)
      } else {
        png(paste(outputFileName,".png",sep = ""), units="cm", width=width, height=height, res=res)
      }
    }
    
    if (noTitle) { par(mar=c(4,4,1,1)+.1) } else { par(mar=c(4,4,4,1)+.1) }
    
    if (is.null(xMin)) { xMin <- min(data[,xAxis]) }
    if (is.null(xMax)) { xMax <- max(data[,xAxis]) }
    if (is.null(yMin)) { yMin <- min(data[,yAxis]) }
    if (is.null(yMax)) { yMax <- max(data[,yAxis]) }
    
    plot(0, type = "n", xlab = "", ylab = "", xlim = c(xMin,xMax), ylim = c(yMin,yMax))
    
    title(xlab = xlab, line = 2.5)
    title(ylab = ylab, line = 2)
    
    if (!noTitle) {
      title(main = title, line = 2.5)
      title(main = subtitle, line = 1.2)      
    }
    
    if (displayBinaryVariable) {
      segments(-1,1,1,1,lty=2)
      segments(1,-1,1,1,lty=2)
    }
    
    for (M in displayMinXAxis) { abline(v = min(data[data$PREM == M,xAxis]), lty = 2) }
    for (M in displayMaxXAxis) { abline(v = max(data[data$PREM == M,xAxis]), lty = 2) }
    for (M in displayMinYAxis) { abline(h = min(data[data$PREM == M,yAxis]), lty = 2) }
    for (M in displayMaxYAxis) { abline(h = max(data[data$PREM == M,yAxis]), lty = 2) }
    
    legendLabel <- c()
    legendColor <- c()
    legendPch <- c()
    legendLwd <- c()
    legendLty <- c()
    
    i <- 1
    
    if (length(preMeasurement) < 9) {
      c2 <- brewer.pal(8,"Dark2")
    } else {
      c2 <- seq(1,length(preMeasurement),1)
    }
    
    
    for(preM in preMeasurement) {
      print(preM)
      d <- data[data$PREM == preM,]
      
      if (suppressSubPhases && nrow(d[d$DISPLAY,]) == 0) next
      if (suppressInterPhases) { d <- d[d$DISPLAY,] }
      
      if (noNegativeValue) { d <- d[d[,xAxis] >= 0 & d[,yAxis] >= 0,] }
      
      if (var == "DELAY") { labels <- d$DELAY }
      if (var == "TIME") { labels <- d$TIME }
      if (var == "SIZE") { labels <- d$SIZE }
      if (var == "CONTRARIAN") { labels <- d$CONTRARIAN }
      
      if (!is.null(color) && !is.null(color[[preM]])) { col <- color[[preM]] } else { col <- c2[i] }
      if (unicolor) { col <- 1 }
      
      if (!is.null(position) && !is.null(position[[preM]])) { pos <- position[[preM]] } else { pos <- 4 }
      if (!is.null(measurementLabel) && !is.null(measurementLabel[[preM]])) { lab <- measurementLabel[[preM]] } else { lab <- preM }
      
      if (phaseDiagram) {
        if (mainPhases) { lwd <- 0.5 } else { lwd <- 4 }
      } else { lwd <- 1 }
      
      lines(d[,xAxis], d[,yAxis], col=col, lwd=lwd)
      
      if (!is.null(pointList)) { d <- d[d[,var] %in% pointList,] } else {
        if (!is.null(pointMin)) { d <- d[d[,var] >= pointMin,] }
        if (!is.null(pointMax)) { d <- d[d[,var] <= pointMax,] }
        if (!is.null(pointStep)) { d <- d[d[,var] %% pointStep == 0,] }        
      }
      
      if (phaseDiagram) {
        d <- d[d$DISPLAY,]
        lines(d[,xAxis], d[,yAxis], col=col, lwd=4)
      } else { points(d[,xAxis], d[,yAxis], pch=19, lwd=2, col=col) }
      
      if (is.null(noLabel) || (noLabel != "ALL" && !(preM %in% noLabel))) {
        if (!is.null(labelList) && !is.null(labelList[["ALL"]])) {
          d <- d[d[,var] %in% labelList[["ALL"]],]
        } else if (!is.null(labelList) && !is.null(labelList[[preM]])) {
          d <- d[d[,var] %in% labelList[[preM]],]
        } else {
          if (!is.null(labelMin)) { d <- d[d[,var] >= labelMin,] }
          if (!is.null(labelMax)) { d <- d[d[,var] <= labelMax,] }
          if (!is.null(labelStep)) { d <- d[d[,var] %% labelStep == 0,] }
        }
        
        text(d[,xAxis], d[,yAxis], labels=d[,var], cex=1, pos=pos)
      }
      
      legendLabel[i] <- lab
      legendColor[i] <- col
      if (phaseDiagram) { legendPch[i] <- NA } else { legendPch[i] <- 19 }
      if (phaseDiagram) { legendLwd[i] <- 3 } else { legendLwd[i] <- 1 }
      legendLty[i] <- 1
      i <- i+1
    }
    
    test <- 0
    
    if (!noLegend) {
      if (legendtitle == "") {
        legend(x=legendPos, legend=legendLabel, col=legendColor, pch=legendPch, lwd=legendLwd, bg="white")
      } else {
        legend(x=legendPos, legend=as.expression(c(legendtitle,legendLabel)), col=c(1,legendColor),
               pch=c(legendvalue,legendPch), lwd=c(0,legendLwd), lty=c(0,legendLty), bg="white")
      }
    }
    
    if (!is.null(addText)) {
      for (i in seq(1,length(addText))) {
        text(addTextX,addTextY,labels=addText,cex=1)
      }
    }
    
    if (print) { dev.off() }
  }
}



plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", update = "NODES",
        preMeasurement = c("EMPTY","AGENT","MICRO","MACRO"), postMeasurement = "MACRO",
        var = "TIME", size = 8, contrarian = 0, time = NULL, delay = 1,
        displayBinaryVariable = TRUE, #displayMaxYAxis = c("MACRO"),
        pointStep = 10, labelStep = 20, labelMax = 100, noLabel = c("EMPTY"), labelList = list("AGENT" = seq(0,100,20)),
        position = list("MACRO" = 2, "MICRO" = 4), noTitle = TRUE,
        print = print, width = width, height = height, outputFileName = "macro_complete_time")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, noTitle = TRUE,
        xAxis = "DATE1", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO"), postMeasurement = "MACRO",
        var = "DATE1", size = 8, date1 = NULL, delay = 1, legendPos = "topright", varMax = 300,
        yMax = 2.1, #displayMinY = c("BETA_EMPTY_AGENT"),
        addText = c("EMPTY","AGENT","MACRO"), addTextX = c(20,150,150), addTextY = c(1.08,1.04,1.6),
        print = print, width = width, height = height, outputFileName = "macro_complete_diagram_time")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, noTitle = TRUE,
        xAxis = "DATE1", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO","SIZE_2","SIZE_3","SIZE_4","SIZE_5","SIZE_6","SIZE_7","SIZE_8","SIZE_9"), postMeasurement = "MACRO", noLegend = TRUE, yMin = 1,
        var = "DATE1", size = 10, date1 = NULL, delay = 1, legendPos = "topright", varMax = 300,
        yMax = 2.1, #displayMinY = c("BETA_EMPTY_AGENT"),
        #suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        addText = c("EMPTY","MACRO"), addTextX = c(20,150), addTextY = c(1.08,1.6),
        print = print, width = width, height = height, outputFileName = "macro_complete_diagram_time_all")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, mainPhases = FALSE, noTitle = TRUE,
        xAxis = "DATE1", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO"), postMeasurement = "MACRO",
        var = "DATE1", size = 8, date1 = NULL, delay = 1, legendPos = "topright", varMax = 300, yMax = 2.1,
        print = print, width = width, height = height, outputFileName = "macro_complete_simple_diagram_time")



plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", noTitle = TRUE,
        preMeasurement = c("EMPTY","AGENT","MICRO","MACRO"), postMeasurement = "MACRO",
        var = "DELAY", size = 10, date1 = 100, delay = NULL, displayMinYAxis = c("MACRO","AGENT"), legendPos = "bottomright",
        noLabel = c("EMPTY"), pointList = c(0,1,10,100), varMin = 1,
        labelList = list("AGENT" = c(1,100), "MACRO" = c(1,10,100), "MICRO" = c(1,10,100)),
        position = list("MACRO" = 2, "MICRO" = 2, "AGENT" = 2),
        print = print, width = width, height = height, outputFileName = "macro_complete_delay")

plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, noTitle = TRUE,
        xAxis = "DELAY", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO"), postMeasurement = "MACRO",
        var = "DELAY", size = 10, date1 = 100, delay = NULL, legendPos = "topright", yMax = 6, varMin = 1,
        addText = c("EMPTY","MACRO","AGENT"), addTextX = c(100,50,100), addTextY = c(1.1,4.5,2.5),
        #displayMaxYAxis = c("BETA_EMPTY_AGENT","BETA_EMPTY_MACRO"),
        print = print, width = width, height = height, outputFileName = "macro_complete_diagram_delay")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, mainPhases = FALSE, noTitle = TRUE,
        xAxis = "DELAY", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO"), postMeasurement = "MACRO",
        var = "DELAY", size = 10, date1 = 100, delay = NULL, legendPos = "topright", yMax = 6, varMin = 1,
        print = print, width = width, height = height, outputFileName = "macro_complete_simple_diagram_delay")



plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", noTitle = TRUE,
        preMeasurement = c("EMPTY","AGENT","MICRO","MACRO","MACRO_AND_AGENT"), postMeasurement = "AGENT",
        var = "DATE1", size = 10, date1 = NULL, delay = 3, noLabel = c("EMPTY"),
        displayBinaryVariable = TRUE, labelMax = 100,
        pointStep = 10, position = list("MACRO" = 2, "MICRO" = 4, "AGENT" = 2),
        labelList = list("AGENT" = c(seq(0,60,10),80,100), "MICRO" = c(seq(0,80,10),100),
                         "MACRO" = c(seq(0,60,10),80), "MACRO_AND_AGENT" = seq(0,60,10)),
        print = print, width = width, height = height, outputFileName = "agent_complete_time")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, noTitle = TRUE,
        xAxis = "DATE1", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO","MACRO_AND_AGENT"),
        postMeasurement = "AGENT", yMax = 50, yMin = 0, noNegativeValue = TRUE,
        var = "DATE1", size = 10, date1 = NULL, delay = 3, legendPos = "topright",
        addText = c("EMPTY","AGENT","MULTILEVEL"), addTextX = c(20,50,130), addTextY = c(-0.5,12.5,28),
        print = print, width = width, height = height, outputFileName = "agent_complete_diagram_time")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, mainPhases = FALSE, noTitle = TRUE,
        xAxis = "DATE1", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO","MACRO_AND_AGENT"),
        postMeasurement = "AGENT", yMax = 50, yMin = 0, noNegativeValue = TRUE,
        var = "DATE1", size = 10, date1 = NULL, delay = 3, legendPos = "topright",
        print = print, width = width, height = height, outputFileName = "agent_complete_simple_diagram_time")



plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", noTitle = TRUE,
        preMeasurement = c("EMPTY","AGENT","MICRO","MACRO","MACRO_AND_AGENT"), postMeasurement = "AGENT",
        var = "DELAY", size = 10, date1 = 0, delay = NULL, noLabel = c("EMPTY","MACRO"),
        displayMinYAxis = c("MACRO","AGENT"), legendPos = "topright",
        position = list("MACRO" = 2, "MICRO" = 2, "AGENT" = 2, "MACRO_AND_AGENT" = 2), yMax = 1.2, varMin = 1,
        labelList = list("AGENT" = c(seq(0,6,1),8,10,20), "MICRO" = c(seq(0,6,1),8,10,20), "MACRO_AND_AGENT" = c(seq(0,6,1),8,10,20)),
        print = print, width = width, height = height, outputFileName = "agent_complete_delay")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, noTitle = TRUE,
        xAxis = "DELAY", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO","MACRO_AND_AGENT"),
        var = "DELAY", size = 10, date1 = 0, delay = NULL, legendPos = "topright", postMeasurement = "AGENT",
        varMax = 30, yMin = 0, yMax = 200, varMin = 1, noNegativeValue = TRUE,
        addText = c("EMPTY","AGENT","MACRO","AGENT","MACRO"), addTextX = c(22,5,22,12,12), addTextY = c(10,40,70,110,100),
        print = print, width = width, height = height, outputFileName = "agent_complete_diagram_delay")


plotIB (inputFileName = "DATA_COMPLETE_FORMATED", type = "COMPLETE", phaseDiagram = TRUE, mainPhases = FALSE, noTitle = TRUE,
        xAxis = "DELAY", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT","MACRO","MACRO_AND_AGENT"),
        var = "DELAY", size = 10, date1 = 0, delay = NULL, legendPos = "topright", postMeasurement = "AGENT",
        varMax = 30, yMin = 0, yMax = 200, varMin = 1, noNegativeValue = TRUE,
        print = print, width = width, height = height, outputFileName = "agent_complete_simple_diagram_delay")



plotIB (inputFileName = "DATA_TWO_COMMUNITIES_FORMATED", type = "TWO_COMMUNITIES", phaseDiagram = TRUE, noTitle = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", postMeasurement = "AGENT", suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        preMeasurement = c("EMPTY","AGENT","MESO_AND_AGENT","MESO1","MACRO_AND_MESO","MACRO","MACRO_MESO_AND_AGENT"),
        var = "DELAY", size = c(5,5), intraRate = c(1,1), interRate = c(0.1,0.1),
        date1 = 0, delay = NULL, noNegativeValue = TRUE,
        yMin = 1, yMax = 600,
        addText = c("EMPTY","AGENT","MESO","MACRO","AGENT","MESO","MESO","MACRO","AGENT","MESO","MACRO"),
        addTextX = c(30,3,28,52,10,10,40,40,19,19,19), addTextY = c(0,25,100,110,300,275,400,375,610,585,560),
        print = print, width = width, height = height, outputFileName = "agent_two_communities_diagram_delay")


plotIB (inputFileName = "DATA_TWO_COMMUNITIES_FORMATED", type = "TWO_COMMUNITIES", phaseDiagram = TRUE, noTitle = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", postMeasurement = "AGENT_MS", suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        preMeasurement = c("EMPTY","AGENT_AE","MESO_AND_AGENT_AE","MESO1_AE","MACRO_AND_MESO_AE","MACRO_AE","MACRO_MESO_AND_AGENT_AE"),
        var = "DELAY", size = c(4,4), intraRate = c(1,1), interRate = c(0.1,0.1),
        date1 = 0, delay = NULL, noNegativeValue = TRUE,
        yMin = 1, yMax = 400,
        print = print, width = width, height = height, outputFileName = "agent_two_communities_diagram_delay")


plotIB (inputFileName = "DATA_TWO_COMMUNITIES_FORMATED", type = "TWO_COMMUNITIES", phaseDiagram = TRUE, noTitle = TRUE, noLegend = TRUE,
        xAxis = "DATE1", yAxis = "BETA", postMeasurement = "AGENT", suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        preMeasurement = c("EMPTY","AGENT","MESO_AND_AGENT","MESO1","MACRO_AND_MESO","MACRO","MACRO_MESO_AND_AGENT","MACRO_AND_AGENT"),
        var = "DATE1", size = c(5,5), intraRate = c(1,1), interRate = c(0.1,0.1),
        date1 = NULL, delay = 3, noNegativeValue = TRUE, yMax = 500, yMin = 0,
        print = FALSE, width = width, height = height, outputFileName = "agent_two_communities_diagram_time")




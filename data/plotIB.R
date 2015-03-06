library(RColorBrewer)



c <- brewer.pal(9,"Set1")

color <- list("MACRO_MS" = c[2], "MICRO_MS" = c[1], "EMPTY_MS" = c[9], "AGENT_MS" = c[3], "MACRO_AND_AGENT" = c[4],
              "MESO1_MS" = c[5], "MESO2_MS" = c[6], "MESO_MS" = c[7], "MESO_AND_AGENT" = "black",
              "MACRO_AND_MESO" = c[7], "MACRO_MESO_AND_AGENT" = c[8])

measurementLabel <- list("MACRO_MS" = "Macroscopic measurement", "MICRO_MS" = "Microscopic measurement",
                         "EMPTY" = "Empty measurement", "AGENT1_MS" = "Agent measurement",
                         "SIZE1_MS" = "1-agent measurement",
                         "SIZE2_MS" = "2-agents measurement",
                         "SIZE3_MS" = "3-agents measurement",
                         "SIZE4_MS" = "4-agents measurement",
                         "SIZE5_MS" = "5-agents measurement",
                         "SIZE6_MS" = "6-agents measurement",
                         "SIZE7_MS" = "7-agents measurement",
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


measurementText <- list(
  "EMPTY" = c("EMPTY"),
  "AGENT1_MS" = c("AGENT"),
  "AGENT1_MESO2_MS" = c("AGENT","MESO2"),
  "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO1","MESO2"),
  "MACRO_MS" = c("MACRO"),
  "AGENT1_MACRO_MS" = c("AGENT","MACRO"),
  "AGENT1_MESO1_MS" = c("AGENT","MESO1"),
  "MESO1_MS" = c("MESO1"),
  "MESO1_MESO2_MS" = c("MESO1","MESO2"),
  "MESO2_MS" = c("MESO2"),
  "MICRO_MS" = c("MICRO"),

  "MACRO_1PC" = c("MACRO_1PC"), "AGENT1_MACRO_1PC" = c("AGENT","MACRO_1PC"),
  "MACRO_5PC" = c("MACRO_5PC"), "AGENT1_MACRO_5PC" = c("AGENT","MACRO_5PC"),
  "MACRO_9PC" = c("MACRO_9PC"), "AGENT1_MACRO_9PC" = c("AGENT","MACRO_9PC"),
  "MACRO_10PC" = c("MACRO_10PC"), "AGENT1_MACRO_10PC" = c("AGENT","MACRO_10PC"),
  "MACRO_20PC" = c(""), "AGENT1_MACRO_20PC" = c(""),
  "MACRO_30PC" = c(""), "AGENT1_MACRO_30PC" = c(""),
  "MACRO_40PC" = c(""), "AGENT1_MACRO_40PC" = c(""),
  "MACRO_50PC" = c("MACRO_50PC"), "AGENT1_MACRO_50PC" = c("AGENT","MACRO_50PC"),
  "MACRO_60PC" = c(""), "AGENT1_MACRO_60PC" = c(""),
  "MACRO_70PC" = c(""), "AGENT1_MACRO_70PC" = c(""),
  "MACRO_80PC" = c(""), "AGENT1_MACRO_80PC" = c(""),
  "MACRO_90PC" = c("MACRO_90PC"), "AGENT1_MACRO_90PC" = c("AGENT","MACRO_90PC"),
  
  "MACRO_MAJ" = c("MACRO_MAJ"), "AGENT1_MACRO_MAJ" = c("AGENT","MACRO_MAJ"),
  "MACRO_2B" = c("MACRO_2B"), "AGENT1_MACRO_2B" = c("AGENT","MACRO_2B"),
  "MACRO_3B" = c("MACRO_3B"), "AGENT1_MACRO_3B" = c("AGENT","MACRO_3B"),
  "MACRO_4B" = c("MACRO_4B"), "AGENT1_MACRO_4B" = c("AGENT","MACRO_4B"),
  "MACRO_6B" = c("MACRO_6B"), "AGENT1_MACRO_6B" = c("AGENT","MACRO_6B"),
  "MACRO_8B" = c("MACRO_8B"), "AGENT1_MACRO_8B" = c("AGENT","MACRO_8B"),
  "MACRO_10B" = c("MACRO_10B"), "AGENT1_MACRO_10B" = c("AGENT","MACRO_10B"),
  "MACRO_12B" = c("MACRO_12B"), "AGENT1_MACRO_12B" = c("AGENT","MACRO_12B"),
  
  "SIZE1_MS" = c(""), "SIZE2_MS" = c(""), "SIZE3_MS" = c(""), "SIZE4_MS" = c(""), "SIZE5_MS" = c(""), "SIZE6_MS" = c(""), "SIZE7_MS" = c(""),
  "AGENT1_SIZE2_MS" = c(""), "AGENT1_SIZE3_MS" = c(""), "AGENT1_SIZE4_MS" = c(""), "AGENT1_SIZE5_MS" = c(""), "AGENT1_SIZE6_MS" = c(""), "AGENT1_SIZE7_MS" = c("")
)


plotIB <- function (inputFileName, modelName, update, preMeasurement, postMeasurement, xAxis = "CURRENT_I", yAxis = "MACRO_I",
                    var, varMin = NULL, varMax = NULL, varStep = NULL, varList = NULL, beta = 1, type = "GENERAL_MODEL",
                    pointMin = NULL, pointMax = NULL, pointStep = NULL, pointList = NULL,
                    labelMin = NULL, labelMax = NULL, labelStep = NULL, labelList = NULL, noLabel = NULL, unicolor = FALSE,
                    size = NULL, time = NULL, delay = NULL, intraRate = NULL, interRate = NULL, contrarian = NULL,
                    xMin = NULL, xMax = NULL, yMin = NULL, yMax = NULL, noTitle = FALSE, onlyPoints = FALSE,
                    phasesNames = FALSE, aggregatedNames = FALSE, minSizeForNames = NULL, boxVarMin = NULL, boxVarMax = NULL,
                    displayBinaryVariable = FALSE, displayMinXAxis = NULL, displayMaxXAxis = NULL,
                    displayMinYAxis = NULL, displayMaxYAxis = NULL, legendPos = "bottomright",
                    addText = NULL, addTextX = NULL, addTextY = NULL, noNegativeValue = FALSE, phaseThreshold = NULL,
                    position = NULL, noLegend = FALSE, phaseDiagram = FALSE, mainPhases = TRUE, withAggregation = FALSE,
                    suppressSubPhases = FALSE, suppressInterPhases = FALSE, measurementText = NULL,
                    print = FALSE, pdf = TRUE, outputFileName = NULL, width = 8, height = 6, res = 600,
                    expId = NULL) {
  
  setwd("~/programming/multilevel_prediction/data/")
  
  if (is.null(outputFileName)) { outputFileName = inputFileName }
  
  if (is.null(size)) { size <- c(NULL,NULL) }
  if (is.null(intraRate)) { intraRate <- c(NULL,NULL) }
  if (is.null(interRate)) { interRate <- c(NULL,NULL) }
  if (is.null(contrarian)) { contrarian <- c(0,0) }
  
  size1 <- size[1]
  size2 <- size[2]
  intraRate1 <- intraRate[1]
  intraRate2 <- intraRate[2]
  interRate1 <- interRate[1]
  interRate2 <- interRate[2]
  contrarian1 <- contrarian[1]
  contrarian2 <- contrarian[2]
  
  
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
  
  if (postMeasurement == "AGENT1_MS" || postMeasurement == "AGENT2_MS") {
    title <- bquote("Predicting a " ~ bold("One-agent Measurement"))
    postMTxt <- bquote(phi[group("{",omega,"}")])
  }
  
  title <- bquote(.(title) ~ " of the " ~ bold(.(modelName)))
  
  tTxt <- time
  if (!is.null(time) && time == -1) { tTxt <- bquote(infinity) }
  
  timeTxt <- bquote("time: " ~ t == .(tTxt) ~ ", ")
  
  delayTxt <- bquote("delay: " ~ tau == .(delay) ~ ", ")
  rateTxt <- bquote("")
  sizeTxt <- bquote("")
  
  contTxt <- bquote("")
  if (contrarian1 > 0 && (contrarian1 == contrarian2 || contrarian2 == 0)) { contTxt <- bquote("contrarian: " ~ c == .(round(contrarian1,2)) ~ ", ") }
  if (contrarian1 > 0 && contrarian2 > 0 && contrarian2 != contrarian1) { contTxt <- bquote("contrarian: " ~ group("(",list(.(round(contrarian1,2)),.(round(contrarian2,2))),")") ~ ", ") }
  
  if (size2 == 0) {
    sizeTxt <- bquote("size: " ~ group("|",X,"|") == .(size) ~ ", ")
  } else {
    sizeTxt <- bquote("size: " ~ group("|",X,"|") == .(size1) + .(size2) ~ ", ")
    rateTxt <- bquote("interaction rates: " ~ omega[1] == .(round(interRate1,2)) ~ " and " ~  omega[2] == .(round(interRate2,2)) ~ ", ")
  }
  
  if (var == "DELAY") {
    subtitle <- bquote("(" ~ .(sizeTxt) ~ .(timeTxt) ~ .(rateTxt) ~ .(contTxt)
                       ~ "and variable delay:" ~ tau %in% ~ group("[",list(0,infinity),"[") ~ ")")
    currentStateTxt <- bquote(X^.(tTxt))
    if (time != 0) { nextStateTxt <- bquote(X^{.(tTxt)+tau}) } else { nextStateTxt <- bquote(X^tau) }
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
    currentStateTxt <- bquote(X^.(tTxt))
    nextStateTxt <- bquote(X^.(time+delay))
    if (time == -1) { nextStateTxt <- bquote(X^(.(tTxt)+.(delay))) }
    if (xAxis != var && yAxis != var) {
      legendtitle <- bquote("Size " ~ group("|",X,"|"))
      legendvalue <- 48 + 0
    }
  }
  
  
  if (var == "CONTRARIAN1") {
    subtitle <- bquote("(" ~ .(sizeTxt) ~ .(timeTxt) ~ .(delayTxt) ~ .(rateTxt)
                       ~ "and variable contrarian rate:" ~ c %in% ~ group("[",list(0,1),"]") ~ ")")
    currentStateTxt <- bquote(X^.(tTxt))
    nextStateTxt <- bquote(X^.(time+delay))
    if (time == -1) { nextStateTxt <- bquote(X^(.(tTxt)+.(delay))) }
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
                    "IB" = bquote("Information Bottleneck with" ~ beta == .(beta)),
                    "CONTRARIAN1" = bquote("Contrarian rate   " ~ c)
  )
  
  xlab <- xAxis
  ylab <- yAxis
  
  if (!is.null(axisLabel[[xAxis]])) { xlab = axisLabel[[xAxis]] }
  if (!is.null(axisLabel[[yAxis]])) { ylab = axisLabel[[yAxis]] }
  
  
  
  # READ AND FILTER DATA
  
  data <- read.csv(paste(inputFileName,".CSV",sep=""), sep = ",")
  data$PREM <- as.character(data$PREM)
  data <- data[data$TYPE == type & data$UPDATE == update & data$POSTM == postMeasurement & data$PREM %in% preMeasurement,]
    
  if (!is.null(varMin)) { data <- data[data[,var] >= varMin,] }
  if (!is.null(varMax)) { data <- data[data[,var] <= varMax,] }
  if (!is.null(varStep)) { data <- data[data[,var] %% varStep == 0,] }        
  
  data <- data[data$SIZE1 == size1 & data$SIZE2 == size2 & data$INTRARATE1 == round(intraRate1,6) & data$INTRARATE2 == round(intraRate2,6) & data$INTERRATE1 == round(interRate1,6) & data$INTERRATE2 == round(interRate2,6),]
  
  if (var == "TIME") {
    data <- data[data$DELAY == delay & data$CONTRARIAN1 == round(contrarian1,6) & data$CONTRARIAN2 == round(contrarian2,6) & data$TIME >= 0,]
    data <- data[with(data, order(data$TIME)), ]
  }
  
  if (var == "SIZE") {
    data <- data[data$TIME == time & data$DELAY == delay & data$CONTRARIAN1 == round(contrarian1,6) & data$CONTRARIAN2 == round(contrarian2,6),]
    data <- data[with(data, order(data$SIZE)), ]
  }
  
  if (var == "DELAY") {
    data <- data[data$TIME == time & data$CONTRARIAN1 == round(contrarian1,6) & data$CONTRARIAN2 == round(contrarian2,6),]
    data <- data[with(data, order(data$DELAY)), ]
  }
  
  if (var == "CONTRARIAN1") {
    data <- data[data$TIME == time & data$DELAY == delay,]
    data <- data[with(data, order(data$CONTRARIAN1)), ]
  }
  
  if (xAxis == "MACRO_COND_H" || yAxis == "MACRO_COND_H") {
    data$MACRO_COND_H <- data$NEXT_MACRO_H - data$MACRO_I
  }
  
  data$MACRO_I <- round(data$MACRO_I,10)
  data$CURRENT_I <- round(data$CURRENT_I,10)
  
  if (xAxis == "BETA" || yAxis == "BETA") {
    newPreMeasurement <- c()
    newData <- data[FALSE,c("PREM",var)]
    
    if (withAggregation) {
      newPreM <- c()
      mList <- as.character(unique(data$PREM))
      for (m in mList) {
        for (preM in preMeasurement) {
          if (substr(m,1,nchar(preM)) == preM) {
            newPreM <- c(newPreM,m)
            break
          }
        }
      }
      preMeasurement <- newPreM
    }
    
    if (phasesNames) {
      boxDisplay <- list()
      boxXPos <- list()
      boxXNorm <- list()
      boxYPos <- list()
      boxYNorm <- list()
      boxSizeMax <- list()
      
      for (i in seq(1,length(preMeasurement))) {
        preM <- preMeasurement[i]
        boxDisplay[[preM]] <- TRUE
        boxXPos[[preM]] <- 0
        boxXNorm[[preM]] <- 0
        boxYPos[[preM]] <- 0
        boxYNorm[[preM]] <- 0
        boxSizeMax[[preM]] <- 0
      }      
    }

    for (v in seq(max(varMin,xMin),min(varMax,xMax))) {
      d <- data[data[,var] == v,]
      pList <- d$PREM
      print (paste(var,v))
      
      for (i in seq(1,length(pList)-1)) {
        for (j in seq((i+1),length(pList))) {
          preM1 <- pList[i]
          preM2 <- pList[j]
          
          d1 <- d[d$PREM == preM1,]
          d2 <- d[d$PREM == preM2,]
          dm <- merge(d1,d2,by=var)
          
          dm$BETA <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y,(dm$CURRENT_I.x - dm$CURRENT_I.y) / (dm$MACRO_I.x - dm$MACRO_I.y),Inf)
          dm$IB.x <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y,dm$CURRENT_I.x - (dm$BETA-1) * dm$MACRO_I.x,dm$CURRENT_I.x)
          dm$IB.y <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y,dm$CURRENT_I.y - (dm$BETA-1) * dm$MACRO_I.y,dm$CURRENT_I.y)
            
          newPreM <- paste("BETA_",preM1,"_",preM2,sep="")
          dm$PREM <- newPreM
          dm$PREM_INF <- ifelse(dm$IB.x > dm$IB.y,preM2,preM1)
          dm$PREM_SUP <- ifelse(dm$IB.x > dm$IB.y,preM1,preM2)
          newData <- rbind(dm[,c("PREM","PREM_INF","PREM_SUP",var,"BETA")],newData)
          newPreMeasurement <- c(newPreMeasurement,newPreM)
          noLabel <- c(noLabel,newPreM)          
        }
      }
    }

    oldMeasurement <- preMeasurement
    preMeasurement <- newPreMeasurement
    data <- newData
    data <- data[data$BETA != Inf & data$BETA != -Inf,]
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

    if (phasesNames) {
      vMin <- max(varMin,xMin)
      if (!is.null(boxVarMin)) { vMin <- max(vMin,boxVarMin) }
      vMax <- min(varMax,xMax)
      if (!is.null(boxVarMax)) { vMax <- min(vMax,boxVarMax) }
      
      for (v in seq(vMin,vMax)) {
        d <- data[data[,var] == v & data$BETA <= yMax & data$BETA >= yMin & data$DISPLAY,]
        mSeq <- unique(c(d$PREM_INF,d$PREM_SUP))
        for (preM in mSeq) {
          bMax <- d[d$PREM_INF == preM,"BETA"]
          bMin <- d[d$PREM_SUP == preM,"BETA"]
          if (length(bMax) == 0) { bMax <- yMax }
          if (length(bMax) > 1) { bMax <- max(bMax) }
          if (length(bMin) == 0) { bMin <- yMin }
          if (length(bMin) > 1) { bMin <- min(bMin) }
          
          boxXPos[[preM]] <- boxXPos[[preM]] + v * (bMax - bMin)
          boxXNorm[[preM]] <- boxXNorm[[preM]] + (bMax - bMin)
          boxYPos[[preM]] <- boxYPos[[preM]] + (bMax + bMin) / 2
          boxYNorm[[preM]] <- boxYNorm[[preM]] + 1
          boxSizeMax[[preM]] <- max(boxSizeMax[[preM]],bMax - bMin)
        }
      }
    }
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
    
    displayMeasurement <- unique(data[data$DISPLAY,"PREM"])
    for(preM in displayMeasurement) {
      print(preM)
      d <- data[data$PREM == preM,]
      
      if (suppressSubPhases && nrow(d[d$DISPLAY,]) == 0) next
      if (suppressInterPhases) { d <- d[d$DISPLAY,] }
      
      if (noNegativeValue) { d <- d[d[,xAxis] >= 0 & d[,yAxis] >= 0,] }
      
      if (var == "DELAY") { labels <- d$DELAY }
      if (var == "TIME") { labels <- d$TIME }
      if (var == "SIZE") { labels <- d$SIZE }
      if (var == "CONTRARIAN1") { labels <- d$CONTRARIAN1 }
      
      if (!is.null(color) && !is.null(color[[preM]])) { col <- color[[preM]] } else { col <- c2[i] }
      if (unicolor) { col <- 1 }
      
      if (!is.null(position) && !is.null(position[[preM]])) { pos <- position[[preM]] } else { pos <- 4 }
      if (!is.null(measurementLabel) && !is.null(measurementLabel[[preM]])) { lab <- measurementLabel[[preM]] } else { lab <- preM }
      
      if (phaseDiagram) {
        if (mainPhases) { lwd <- 0.5 } else { lwd <- 4 }
      } else { lwd <- 1 }
      
      od <- d[order(d[,var]),]
      x <- od[,xAxis]
      y <- od[,yAxis]
      xd <- seq(x[1],x[length(x)])
      yd <- rep(NA,length(xd))
      yd[x-x[1]+1] <- y
      
      if (!onlyPoints) { lines(xd, yd, col=col, lwd=lwd) }
      points(x, y, col=col, lwd=lwd, pch=20)
      
      if (!is.null(pointList)) { d <- d[d[,var] %in% pointList,] } else {
        if (!is.null(pointMin)) { d <- d[d[,var] >= pointMin,] }
        if (!is.null(pointMax)) { d <- d[d[,var] <= pointMax,] }
        if (!is.null(pointStep)) {
          if (var == "CONTRARIAN1") {
            d <- d[round(d[,var]*10000) %% round(pointStep*10000) == 0,]              
          } else {
            d <- d[d[,var] %% pointStep == 0,]
          }
        }        
      }
      
      if (phaseDiagram) {
        if (!onlyPoints) { lines(xd, yd, col=col, lwd=4) }
      } else { points(d[,xAxis], d[,yAxis], pch=19, lwd=2, col=col) }
      
      if (is.null(noLabel) || (noLabel != "ALL" && !(preM %in% noLabel))) {
        if (!is.null(labelList) && !is.null(labelList[["ALL"]])) {
          d <- d[d[,var] %in% labelList[["ALL"]],]
        } else if (!is.null(labelList) && !is.null(labelList[[preM]])) {
          d <- d[d[,var] %in% labelList[[preM]],]
        } else {
          if (!is.null(labelMin)) { d <- d[d[,var] >= labelMin,] }
          if (!is.null(labelMax)) { d <- d[d[,var] <= labelMax,] }
          if (!is.null(labelStep)) {
            if (var == "CONTRARIAN1") {
              d <- d[round(d[,var]*10000) %% round(labelStep*10000) == 0,]              
            } else {
              d <- d[d[,var] %% labelStep == 0,]
            }
          }
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
    
    if (phasesNames) {
      for (i in seq(1,length(oldMeasurement))) {
        preM <- oldMeasurement[i]
        if (boxDisplay[[preM]]) {
          if (is.null(minSizeForNames) || boxSizeMax[[preM]] > minSizeForNames) {
            x <- boxXPos[[preM]] / boxXNorm[[preM]]
            y <- boxYPos[[preM]] / boxYNorm[[preM]]
            
            p <- preM
            add <- c()
            cut <- regexpr("_|",preM,fixed=T)[1]
            if (cut >= 0) {
              p <- substr(preM,1,cut-1)
              add <- c(substr(preM,cut+1,nchar(preM)))
            }
            if (aggregatedNames) {
              if (add == paste("|0-",size1+size2,"|",sep="")) {
                p <- "EMPTY"
                add <- c()
              } else if (add == paste("|",paste(paste(seq(0,size1+size2),"|",sep=""),collapse=""),sep="")) {
                add <- c()
              } else {
                p <- add[1]
                add <- c()
              }
            }
            if (!is.null(measurementText) && !is.null(measurementText[[p]])) { p <- measurementText[[p]] }
            txt <- c(p,add)
            text(x,y,labels=paste(txt,collapse="\n"),cex=1)            
          }
        }
      }
    }
    
    if (print) { dev.off() }
  }
}


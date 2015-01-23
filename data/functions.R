library(RColorBrewer)


plotIB <- function (inputFileName, modelName, update, preMeasurement, postMeasurement, xAxis = "CURRENT_I", yAxis = "MACRO_I",
                    var, varMin = NULL, varMax = NULL, varStep = NULL, varList = NULL, beta = 1, type = "GENERAL_MODEL",
                    pointMin = NULL, pointMax = NULL, pointStep = NULL, pointList = NULL,
                    labelMin = NULL, labelMax = NULL, labelStep = NULL, labelList = NULL, noLabel = NULL, unicolor = FALSE,
                    size = NULL, time = NULL, delay = NULL, intraRate = NULL, interRate = NULL, contrarian = NULL,
                    xMin = NULL, xMax = NULL, yMin = NULL, yMax = NULL, noTitle = FALSE, phasesNames = FALSE,
                    displayBinaryVariable = FALSE, displayMinXAxis = NULL, displayMaxXAxis = NULL,
                    displayMinYAxis = NULL, displayMaxYAxis = NULL, legendPos = "bottomright",
                    addText = NULL, addTextX = NULL, addTextY = NULL, noNegativeValue = FALSE,
                    position = NULL, noLegend = FALSE, phaseDiagram = FALSE, mainPhases = TRUE,
                    suppressSubPhases = FALSE, suppressInterPhases = FALSE, measurementText = NULL,
                    print = FALSE, pdf = TRUE, outputFileName = NULL, width = 8, height = 6, res = 600,
                    expId = NULL) {
  
  setwd("C:/Users/Robin/Mes projets/programming/multilevel_prediction/data")
  
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
  
  c <- brewer.pal(9,"Set1")
  
  color <- list("MACRO_MS" = c[2], "MICRO_MS" = c[1], "EMPTY_MS" = c[9], "AGENT_MS" = c[3], "MACRO_AND_AGENT" = c[4],
                "MESO1_MS" = c[5], "MESO2_MS" = c[6], "MESO_MS" = c[7], "MESO_AND_AGENT" = "black",
                "MACRO_AND_MESO" = c[7], "MACRO_MESO_AND_AGENT" = c[8])
  
  measurementLabel <- list("MACRO_MS" = "Macroscopic measurement", "MICRO_MS" = "Microscopic measurement",
                           "EMPTY" = "Empty measurement", "AGENT1_MS" = "One-agent measurement",
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
  
  data <- read.csv(paste(inputFileName,".csv",sep=""), sep = ",")
  data <- data[data$TYPE == type & data$UPDATE == update & data$POSTM == postMeasurement,]
  
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
  
  data$MACRO_I <- round(data$MACRO_I,5)
  data$CURRENT_I <- round(data$CURRENT_I,5)
  
  if (xAxis == "BETA" || yAxis == "BETA") {
    newPreMeasurement <- c()
    data <- data[,c("PREM",var,"CURRENT_I","MACRO_I")]
    data$BETA <- NA
    data$PREM_INF <- NA
    data$PREM_SUP <- NA
    
    if (phasesNames) {
      boxDisplay <- list()
      
      boxLeft <- list()
      boxRight <- list()
      boxUp <- list()
      boxDown <- list()
      
      boxXPos <- list()
      boxXNorm <- list()
      boxYPos <- list()
      boxYNorm <- list()
      
      for (i in seq(1,length(preMeasurement))) {
        preM <- preMeasurement[i]
        boxDisplay[[preM]] <- TRUE
        
        boxLeft[[preM]] <- xMax
        boxRight[[preM]] <- xMin
        boxUp[[preM]] <- NA
        boxDown[[preM]] <- NA
        
        boxXPos[[preM]] <- 0
        boxXNorm[[preM]] <- 0
        boxYPos[[preM]] <- 0
        boxYNorm[[preM]] <- 0
      }      
    }
    
    for (i in seq(1,length(preMeasurement)-1)) {
      for (j in seq((i+1),length(preMeasurement))) {
        preM1 <- preMeasurement[i]
        preM2 <- preMeasurement[j]
        d1 <- data[data$PREM == preM1,]
        d2 <- data[data$PREM == preM2,]
        d <- merge(d1,d2,by=var)
        
        d$BETA <- ifelse(d$MACRO_I.x != d$MACRO_I.y,(d$CURRENT_I.x - d$CURRENT_I.y) / (d$MACRO_I.x - d$MACRO_I.y),Inf)
        d$IB.x <- ifelse(d$MACRO_I.x != d$MACRO_I.y,d$CURRENT_I.x - (d$BETA-1) * d$MACRO_I.x,d$CURRENT_I.x)
        d$IB.y <- ifelse(d$MACRO_I.x != d$MACRO_I.y,d$CURRENT_I.y - (d$BETA-1) * d$MACRO_I.y,d$CURRENT_I.y)
        
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
    oldMeasurement <- preMeasurement
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
      
      if (phasesNames && data[r,"DISPLAY"] && beta >= yMin && beta <= yMax && v <= xMax && v >= xMin) {
        boxUp[[prem_inf]] <- max(boxUp[[prem_inf]],beta,na.rm=TRUE)
        boxDown[[prem_sup]] <- min(boxDown[[prem_sup]],beta,na.rm=TRUE)
        boxLeft[[prem_inf]] <- min(boxLeft[[prem_inf]],v)
        boxLeft[[prem_sup]] <- min(boxLeft[[prem_sup]],v)
        boxRight[[prem_inf]] <- max(boxRight[[prem_inf]],v)
        boxRight[[prem_sup]] <- max(boxRight[[prem_sup]],v)
      }
    }
    
    if (phasesNames) {
      for (v in seq(max(varMin,xMin),min(varMax,xMax))) {
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
        }
      }
      
      for (i in seq(1,length(oldMeasurement))) {
        preM <- oldMeasurement[i]
        if (is.na(boxDown[[preM]]) && is.na(boxUp[[preM]])) {
          boxDisplay[[preM]] <- FALSE
        } else {
          if (is.na(boxDown[[preM]])) { boxDown[[preM]] <- yMin }
          if (is.na(boxUp[[preM]])) { boxUp[[preM]] <- yMax }          
        }
      }
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
      #      if (suppressInterPhases) { d[d$DISPLAY,var] <- NA }
      
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
      
      lines(d[,xAxis], d[,yAxis], col=col, lwd=lwd)
      
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
          #x <- (boxRight[[preM]] + boxLeft[[preM]])/2
          #y <- (boxUp[[preM]] + boxDown[[preM]])/2
          x <- boxXPos[[preM]] / boxXNorm[[preM]]
          y <- boxYPos[[preM]] / boxYNorm[[preM]]
          txt <- c(preM)
          if (!is.null(measurementText) && !is.null(measurementText[[preM]])) { txt <- measurementText[[preM]] }
          text(x,y,labels=paste(txt,collapse="\n"),cex=1)
        }
      }
    }
    
    if (print) { dev.off() }
  }
}



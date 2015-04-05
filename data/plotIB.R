library(RColorBrewer)


colorSet <- brewer.pal(9,"Set1")

colorHide <- "darkgrey"
pchHide <- 21

color <- list(
    "MACRO_MS" = colorSet[2],
    "MICRO_MS" = colorSet[1],
    "EMPTY" = "black",
    "AGENT1_MS" = colorSet[3],
    "MESO1_MS" = colorSet[5],
    "MESO2_MS" = colorSet[6]
    )

pchList <- list(
    "MACRO_MS" = 25,
    "MICRO_MS" = 24,
    "EMPTY" = 23,
    "AGENT_MS" = 22,
    "MESO1_MS" = 4,
    "MESO2_MS" = 5
    )

measurementLabel <- list(
    "EMPTY" = "EMPTY",
    "MACRO_MS" = "MACRO",
    "MICRO_MS" = "MICRO",
    "AGENT1_MS" = "Agent measurement",
    "MESO1" = "Mesoscopic measurement",
    "MESO2" = "Mesoscopic measurement",

    "SIZE1_MS" = "1-agent measurement",
    "SIZE2_MS" = "2-agents measurement",
    "SIZE3_MS" = "3-agents measurement",
    "SIZE4_MS" = "4-agents measurement",
    "SIZE5_MS" = "5-agents measurement",
    "SIZE6_MS" = "6-agents measurement",
    "SIZE7_MS" = "7-agents measurement",

    "BETA_MACRO_EMPTY" = "IB-empty = IB-macro",
    "BETA_EMPTY_MACRO" = "IB-empty = IB-macro",
    "BETA_MACRO_AGENT" = "IB-agent = IB-macro",
    "BETA_AGENT_MACRO" = "IB-agent = IB-macro",
    "BETA_EMPTY_AGENT" = "IB-empty = IB-agent",
    "BETA_AGENT_EMPTY" = "IB-empty = IB-agent",

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

    "NEIGHBORHOOD1_MS" = c("N1"),
    "NEIGHBORHOOD2_MS" = c("N2"),
    "NEIGHBORHOOD3_MS" = c("N3"),
    "NEIGHBORHOOD4_MS" = c("N4"),
    
    "MACRO_1PC" = c("MACRO_1PC"),
    "MACRO_5PC" = c("MACRO_5PC"),
    "MACRO_9PC" = c("MACRO_9PC"),
    "MACRO_10PC" = c("MACRO_10PC"),
    "MACRO_20PC" = c(""),
    "MACRO_30PC" = c(""),
    "MACRO_40PC" = c(""),
    "MACRO_50PC" = c("MACRO_50PC"),
    "MACRO_60PC" = c(""),
    "MACRO_70PC" = c(""),
    "MACRO_80PC" = c(""),
    "MACRO_90PC" = c("MACRO_90PC"),

    "AGENT1_MACRO_1PC" = c("AGENT","MACRO_1PC"),
    "AGENT1_MACRO_5PC" = c("AGENT","MACRO_5PC"),
    "AGENT1_MACRO_9PC" = c("AGENT","MACRO_9PC"),
    "AGENT1_MACRO_10PC" = c("AGENT","MACRO_10PC"),
    "AGENT1_MACRO_20PC" = c(""),
    "AGENT1_MACRO_30PC" = c(""),
    "AGENT1_MACRO_40PC" = c(""),
    "AGENT1_MACRO_50PC" = c("AGENT","MACRO_50PC"),
    "AGENT1_MACRO_60PC" = c(""),
    "AGENT1_MACRO_70PC" = c(""),
    "AGENT1_MACRO_80PC" = c(""),
    "AGENT1_MACRO_90PC" = c("AGENT","MACRO_90PC"),
    
    "MACRO_MAJ" = c("MACRO_MAJ"),
    "MACRO_2B" = c("MACRO_2B"),
    "MACRO_3B" = c("MACRO_3B"),
    "MACRO_4B" = c("MACRO_4B"),
    "MACRO_6B" = c("MACRO_6B"),
    "MACRO_8B" = c("MACRO_8B"),
    "MACRO_10B" = c("MACRO_10B"),
    "MACRO_12B" = c("MACRO_12B"),

    "AGENT1_MACRO_MAJ" = c("AGENT","MACRO_MAJ"),
    "AGENT1_MACRO_2B" = c("AGENT","MACRO_2B"),
    "AGENT1_MACRO_3B" = c("AGENT","MACRO_3B"),
    "AGENT1_MACRO_4B" = c("AGENT","MACRO_4B"),
    "AGENT1_MACRO_6B" = c("AGENT","MACRO_6B"),
    "AGENT1_MACRO_8B" = c("AGENT","MACRO_8B"),
    "AGENT1_MACRO_10B" = c("AGENT","MACRO_10B"),
    "AGENT1_MACRO_12B" = c("AGENT","MACRO_12B"),
    
    "SIZE1_MS" = c("S1"),
    "SIZE2_MS" = c("S2"),
    "SIZE3_MS" = c("S3"),
    "SIZE4_MS" = c("S4"),
    "SIZE5_MS" = c("S5"),
    "SIZE6_MS" = c("S6"),
    "SIZE7_MS" = c("S7"),

    "AGENT1_SIZE2_MS" = c(""),
    "AGENT1_SIZE3_MS" = c(""),
    "AGENT1_SIZE4_MS" = c(""),
    "AGENT1_SIZE5_MS" = c(""),
    "AGENT1_SIZE6_MS" = c(""),
    "AGENT1_SIZE7_MS" = c("")
    )


plotIB <- function (
    expId = NULL,

    inputFileName, type = "GENERAL_MODEL", update = "EDGES",
    size = NULL, time = NULL, delay = NULL,
    intraRate = NULL, interRate = NULL, contrarian = NULL,
    preMeasurement, postMeasurement,
    var, varMin = NULL, varMax = NULL, varStep = NULL, varList = NULL,

    xAxis = "CURRENT_I", yAxis = "MACRO_I", beta = 1,
    xMin = NULL, xMax = NULL, yMin = NULL, yMax = NULL,
    pointMin = NULL, pointMax = NULL, pointStep = NULL, pointList = NULL,
    labelMin = NULL, labelMax = NULL, labelStep = NULL, labelList = NULL,
    labelPos = NULL, noLabel = NULL, hide = NULL, addLabel = NULL,

    modelName = NULL, noTitle = FALSE,
    noLegend = NULL, legendPos = "bottomright",
    measurementText = NULL, displayMinYAxis = NULL, displayMaxYAxis = NULL,
    displayBinaryVariable = FALSE, displayMinXAxis = NULL, displayMaxXAxis = NULL,
    addText = NULL, addTextX = NULL, addTextY = NULL,
    
    phaseDiagram = FALSE, mainPhases = TRUE, withAggregation = FALSE,
    noNegativeValue = FALSE, phaseThreshold = NULL,
    suppressSubPhases = FALSE, suppressInterPhases = FALSE,
    phasesNames = FALSE, aggregatedNames = FALSE,
    minSizeForNames = NULL, boxVarMin = NULL, boxVarMax = NULL,
    unicolor = FALSE, onlyPoints = FALSE,
    
    print = FALSE, pdf = TRUE, outputFileName = NULL,
    width = 8, height = 6, res = 600
    ) {
    
    #setwd("~/programming/multilevel_prediction/data/")
    
    if (is.null(outputFileName)) { outputFileName = inputFileName }
    
    if (is.null(size)) { size <- c(NULL,NULL) }
    if (is.null(intraRate)) { intraRate <- c(NULL,NULL) }
    if (is.null(interRate)) { interRate <- c(NULL,NULL) }
    if (is.null(contrarian)) { contrarian <- c(NULL,NULL) }
    
    size1 <- size[1]
    size2 <- size[2]
    intraRate1 <- intraRate[1]
    intraRate2 <- intraRate[2]
    interRate1 <- interRate[1]
    interRate2 <- interRate[2]
    contrarian1 <- contrarian[1]
    contrarian2 <- contrarian[2]

    if (is.null(varStep)) { varStep <- 1 }
    preMeasurement <- rev(preMeasurement)
    
                                        # MAKE TITLE AND SUBTITLE
    title <- ""
    subtitle <- ""
    legendtitle <- ""
    
    postMTxt <- bquote(Phi)
    
    if (postMeasurement == "MACRO_MS") {
        title <- bquote("Predicting the Macroscopic Measurement")
        postMTxt <- bquote(phi[T])
    }
    
    if (postMeasurement == "MICRO_MS") {
        title <- bquote("Predicting the Microscopic Measurement")
    }
    
    if (postMeasurement == "AGENT1_MS" || postMeasurement == "AGENT2_MS") {
        title <- bquote("Predicting the Agent Measurement")
        postMTxt <- bquote(phi[group("{",omega,"}")])
    }
    
    title <- bquote(bold(.(title) ~ " in the " ~ .(modelName)))
    
    tTxt <- time
    if (!is.null(time) && time == -1) { tTxt <- bquote(infinity) }
    
    timeTxt <- bquote("time " ~ t == .(tTxt) ~ ", ")
    
    delayTxt <- bquote("horizon " ~ tau == .(delay) ~ ", ")
    rateTxt <- bquote("")
    sizeTxt <- bquote("")
    
    contTxt <- bquote("")
    if (contrarian1 > 0 && (contrarian1 == contrarian2 || contrarian2 == 0)) {
        contTxt <- bquote("contrarian rate " ~ c == .(round(contrarian1,2)) ~ ", ")
    }
    if (contrarian1 > 0 && contrarian2 > 0 && contrarian2 != contrarian1) {
        contTxt <- bquote("contrarian rate " ~ group("(",list(.(round(contrarian1,2)),.(round(contrarian2,2))),")") ~ ", ")
    }
    
    if (size2 == 0) {
        sizeTxt <- bquote("size " ~ N == .(size) ~ ", ")
    } else {
        sizeTxt <- bquote("size " ~ N == .(size1) + .(size2) ~ ", ")
        rateTxt <- bquote("interaction rates " ~ omega[1] == .(round(interRate1,2))
                          ~ " and " ~  omega[2] == .(round(interRate2,2)) ~ ", ")
    }
    
    if (var == "DELAY") {
        subtitle <- bquote(.(sizeTxt) ~ .(timeTxt) ~ .(rateTxt) ~ .(contTxt)
                           ~ "variable horizon" ~ tau %in%
                           ~ group("[",list(0,infinity),"["))
        currentStateTxt <- bquote(X^.(tTxt))
        if (time != 0) {
            nextStateTxt <- bquote(X^{.(tTxt)+tau})
        } else {
            nextStateTxt <- bquote(X^tau)
        }
        if (xAxis != var && yAxis != var) {
            legendtitle <- bquote("Delay " ~ tau)
            legendvalue <- 48 + 0
        }
    }  
    
    if (var == "TIME") {
        subtitle <- bquote(.(sizeTxt) ~ .(delayTxt) ~ .(rateTxt) ~ .(contTxt)
                           ~ "variable time" ~ t %in%
                           ~ group("[",list(0,infinity),"["))
        currentStateTxt <- bquote(X^t)
        if (delay > 0) { nextStateTxt <- bquote(X^{t+.(delay)}) } else { nextStateTxt <- bquote(X^t) }
        if (xAxis != var && yAxis != var) {
            legendtitle <- bquote("Time " ~ t)
            legendvalue <- 48 + 0
        }
    }
    
    if (var == "SIZE") {
        subtitle <- bquote(.(timeTxt) ~ .(delayTxt) ~ .(rateTxt) ~ .(contTxt)
                           ~ "variable size" ~ group("|",X,"|") %in%
                           ~ group("[",list(2,infinity),"["))
        currentStateTxt <- bquote(X^.(tTxt))
        nextStateTxt <- bquote(X^.(time+delay))
        if (time == -1) { nextStateTxt <- bquote(X^(.(tTxt)+.(delay))) }
        if (xAxis != var && yAxis != var) {
            legendtitle <- bquote("Size " ~ group("|",X,"|"))
            legendvalue <- 48 + 0
        }
    }
    
    
    if (var == "CONTRARIAN1") {
        subtitle <- bquote(.(sizeTxt) ~ .(timeTxt) ~ .(delayTxt) ~ .(rateTxt)
                           ~ "variable contrarian rate" ~ c %in%
                           ~ group("[",list(0,1),"]"))
        currentStateTxt <- bquote(X^.(tTxt))
        nextStateTxt <- bquote(X^.(time+delay))
        if (time == -1) { nextStateTxt <- bquote(X^(.(tTxt)+.(delay))) }
        if (xAxis != var && yAxis != var) {
            legendtitle <- bquote("Contrarian rate " ~ c)
            legendvalue <- 48 + 0
        }
    }
    
#    axisLabel <- list(
#        "CURRENT_I" = bquote("Model Complexity   " ~ H
#            ~ bgroup("(",phi ~ group("(",.(currentStateTxt),")"),")")),
#        "MACRO_I" = bquote("Predictive Capacity   " ~ I
#            ~ bgroup("(",phi ~ group("(",.(currentStateTxt),")") ~ ";"
#                     ~ .(postMTxt) ~ group("(",.(nextStateTxt),")"),")")),
#        "MACRO_COND_H" = bquote("Non-predicted Complexity   " ~ H
#            ~ bgroup("(",.(postMTxt) ~ group("(",.(nextStateTxt),")") ~ "|"
#                     ~ phi ~ group("(",.(currentStateTxt),")"),")")),
#        "TIME" = bquote("Time   " ~ t),
#        "DELAY" = bquote("Delay   " ~ tau),
#        "BETA" = bquote("Trade-off Parameter   " ~ beta),
#        "IB" = bquote("Information Bottleneck with" ~ beta == .(beta)),
#        "CONTRARIAN1" = bquote("Contrarian rate   " ~ c)
#        )

    axisLabel <- list(
        "CURRENT_I" = bquote("Model Complexity (in bits)"),
        "MACRO_I" = bquote("Predictive Capacity (in bits)"),
        "TIME" = bquote("Time " ~ t),
        "DELAY" = bquote("Horizon " ~ tau),
        "BETA" = bquote("Trade-off Parameter " ~ beta)
        )

    xlab <- xAxis
    ylab <- yAxis
    
    if (!is.null(axisLabel[[xAxis]])) { xlab = axisLabel[[xAxis]] }
    if (!is.null(axisLabel[[yAxis]])) { ylab = axisLabel[[yAxis]] }
    
    
    
                                        # READ AND FILTER DATA
    
    data <- read.csv(paste(inputFileName,".CSV",sep=""), sep = ",")
    data$PREM <- as.character(data$PREM)
    data$POSTM <- as.character(data$POSTM)

    data <- data[data$TYPE %in% type
                 & (var == "UPDATE" | data$UPDATE %in% update)
                 & (var == "SIZE1" | data$SIZE1 %in% size1)
                 & (var == "SIZE2" | data$SIZE2 %in% size2)
                 & (var == "INTRARATE1" | data$INTRARATE1 %in% intraRate1)
                 & (var == "INTRARATE2" | data$INTRARATE2 %in% intraRate2)
                 & (var == "INTERRATE1" | data$INTERRATE1 %in% interRate1)
                 & (var == "INTERRATE2" | data$INTERRATE2 %in% interRate2)
                 & (var == "CONTRARIAN1" | data$CONTRARIAN1 %in% contrarian1)
                 & (var == "CONTRARIAN2" | data$CONTRARIAN2 %in% contrarian2)
                 & (withAggregation | var == "PREM" | data$PREM %in% preMeasurement)
                 & (var == "POSTM" | data$POSTM %in% postMeasurement)
                 & (var == "TIME" | data$TIME %in% time)
                 & (var == "DELAY" | data$DELAY %in% delay)
                 ,]
    
    if (!is.null(varMin)) { data <- data[data[,var] >= varMin,] }
    if (!is.null(varMax)) { data <- data[data[,var] <= varMax,] }
    if (!is.null(varStep)) { data <- data[data[,var] %% varStep == 0,] }        

    if (nrow(data) == 0) { stop("NO RESULT!") }

    data <- data[with(data, order(data[,var])),]
    
    mPrec <- 10
    data$CURRENT_MICRO_H <- round(data$CURRENT_MICRO_H,mPrec)
    data$CURRENT_MACRO_H <- round(data$CURRENT_MACRO_H,mPrec)
    data$NEXT_MICRO_H <- round(data$NEXT_MICRO_H,mPrec)
    data$NEXT_MACRO_H <- round(data$NEXT_MACRO_H,mPrec)
    data$MICRO_I <- round(data$MICRO_I,mPrec)
    data$MACRO_I <- round(data$MACRO_I,mPrec)
    data$CURRENT_I <- round(data$CURRENT_I,mPrec)
    data$NEXT_I <- round(data$NEXT_I,mPrec)

    if (xAxis == "MACRO_COND_H" || yAxis == "MACRO_COND_H") {
        data$MACRO_COND_H <- data$NEXT_MACRO_H - data$MACRO_I
    }


    
                                        # COMPUTE IB-DIAGRAM
   
    data$DISPLAY <- TRUE
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

        step <- 1
        if (!is.null(varStep)) { step <- varStep }
        for (v in seq(max(varMin,xMin),min(varMax,xMax),step)) {
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
                    
                    dm$BETA <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y, (dm$CURRENT_I.x - dm$CURRENT_I.y) / (dm$MACRO_I.x - dm$MACRO_I.y), Inf)
                    dm$IB.x <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y, dm$CURRENT_I.x - (dm$BETA-1) * dm$MACRO_I.x, dm$CURRENT_I.x)
                    dm$IB.y <- ifelse(dm$MACRO_I.x != dm$MACRO_I.y, dm$CURRENT_I.y - (dm$BETA-1) * dm$MACRO_I.y, dm$CURRENT_I.y)
                    
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
    
    if (print) {
        if (pdf) {  
            pdf(paste(outputFileName,".pdf",sep = ""), useDingbats=FALSE,
                width=width, height=height)
        } else {
            png(paste(outputFileName,".png",sep = ""),
                units="cm", width=width, height=height, res=res)
        }
    }
    
    if (noTitle) { par(mar=c(3,3,0,0)+.1) } else { par(mar=c(4,4,4,1)+.1) }
    
    if (is.null(xMin)) { xMin <- min(data[,xAxis]) }
    if (is.null(xMax)) { xMax <- max(data[,xAxis]) }
    if (is.null(yMin)) { yMin <- min(data[,yAxis]) }
    if (is.null(yMax)) { yMax <- max(data[,yAxis]) }
    
    plot(0, type = "n", axes = F, xlab = NA, ylab = NA, xlim = c(xMin,xMax), ylim = c(yMin,yMax))
    
    title(xlab = xlab, line = 1.7, cex.lab = 1.3)
    title(ylab = ylab, line = 1.7, cex.lab = 1.3)
    axis(side = 1, tck = -.01, labels = NA)
    axis(side = 2, tck = -.01, labels = NA)
    axis(side = 1, lwd = 0, line = -0.5)
    axis(side = 2, lwd = 0, line = -0.5)

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
        colorSet <- brewer.pal(8,"Dark2")
    } else {
        colorSet <- seq(1,length(preMeasurement),1)
    }

    if (xAxis == "BETA" || yAxis == "BETA") {
        if (suppressSubPhases) { displayMeasurement <- unique(data[data$DISPLAY,"PREM"]) }
        else { displayMeasurement <- unique(data[,"PREM"]) }
    } else { displayMeasurement <- preMeasurement }

    for(preM in displayMeasurement) {
        print(preM)
        d <- data[data$PREM == preM,]
        
        if (suppressSubPhases && nrow(d[d$DISPLAY,]) == 0) next
        if (suppressInterPhases) { d <- d[d$DISPLAY,] }        
        if (noNegativeValue) { d <- d[d[,xAxis] >= 0 & d[,yAxis] >= 0,] }

        if (nrow(d) == 0) { next }
        
        if (var == "DELAY") { labels <- d$DELAY }
        if (var == "TIME") { labels <- d$TIME }
        if (var == "SIZE") { labels <- d$SIZE }
        if (var == "CONTRARIAN1") { labels <- d$CONTRARIAN1 }

        if (!is.null(hide) && preM %in% hide) {
            col <- colorHide
        } else {
            if (!is.null(color) && !is.null(color[[preM]])) {
                col <- color[[preM]]
            } else {
                col <- colorSet[i]
            }
            if (unicolor) { col <- 1 }
        }

        if (!is.null(pchList) && !is.null(pchList[[preM]])) {
            pch <- pchList[[preM]]
        } else {
            pch <- pchHide
        }

        if (!is.null(labelPos) && !is.null(labelPos[[preM]])) {
            pos <- labelPos[[preM]]
        } else {
            pos <- 4
        }
        
        if (!is.null(measurementLabel) && !is.null(measurementLabel[[preM]])) {
            lab <- measurementLabel[[preM]]
        } else {
            lab <- preM
        }
        
        if (phaseDiagram) {
            if (mainPhases) { lwd <- 4 } else { lwd <- 0.5 }
        } else { lwd <- 1 }
        

                                        # draw lines
        if (!onlyPoints) {
            if (phaseDiagram) {
                od <- d[order(d[,var]),]
                x <- od[,xAxis]
                y <- od[,yAxis]        
                xd <- seq(x[1],x[length(x)],varStep)
                yd <- rep(NA,length(xd))
                yd[(x-x[1])/varStep+1] <- y
                if (withAggregation) { print(max(y)) }

                lines(xd, yd, col=col, lwd=lwd)
            } else {
                lines(d[,xAxis], d[,yAxis], pch=19, lwd=2, col=col)
            }
        }
        
                                        # draw dots
        if (!is.null(pointList) && !is.null(pointList[[preM]])) {
            d <- d[d[,var] %in% pointList[[preM]],]
        } else if (!is.null(pointList) && !is.null(pointList[["ALL"]])) {
            d <- d[d[,var] %in% pointList[["ALL"]],]
        } else {
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
        
        points(d[,xAxis], d[,yAxis], pch=pch, lwd=2, col=col, bg=col)

                                        # draw labels
        if (!is.null(addLabel) && !is.null(addLabel[[preM]])) {
            addL <- addLabel[[preM]]
            text(d[as.integer(addL[1]),xAxis], d[as.integer(addL[1]),yAxis], labels=bquote(bold(.(addL[3]))), cex=1, pos=as.integer(addL[2]), col=col)
        }

        if (!is.null(labelList) && !is.null(labelList[[preM]])) {
            d <- d[d[,var] %in% labelList[[preM]],]
        } else if (!is.null(labelList) && !is.null(labelList[["ALL"]])) {
            d <- d[d[,var] %in% labelList[["ALL"]],]                
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

        if (is.null(noLabel) || (noLabel != "ALL" && !(preM %in% noLabel))) {
            lArray <- d[,var]
            if (var == "TIME") { lArray <- paste(bquote(t),"=",lArray,sep="") }
            text(d[,xAxis], d[,yAxis], labels=lArray, cex=1, pos=pos)
        }

        if (is.null(noLegend) || (noLegend != "ALL" && !(preM %in% noLegend))) {
            legendLabel[i] <- lab
            legendColor[i] <- col
            if (phaseDiagram) { legendPch[i] <- NA } else { legendPch[i] <- pch }
            if (phaseDiagram) { legendLwd[i] <- 3 } else { legendLwd[i] <- 1 }
            legendLty[i] <- 1
            i <- i+1
        }
    }
    
    test <- 0

    
                                        # PRINT LEGEND
    
    if (is.null(noLegend) || noLegend != "ALL") {
        if (legendtitle == "") {
            legend(x=legendPos, legend=rev(legendLabel), col=rev(legendColor), pt.bg=c(1,rev(legendColor)), pch=rev(legendPch), lwd=rev(legendLwd), bg="white")
        } else {
            legend(x=legendPos, legend=as.expression(c(legendtitle,rev(legendLabel))), col=c(1,rev(legendColor)), pt.bg=c(1,rev(legendColor)),
                   pch=c(legendvalue,rev(legendPch)), lwd=c(0,rev(legendLwd)), lty=c(0,rev(legendLty)), bg="white")
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



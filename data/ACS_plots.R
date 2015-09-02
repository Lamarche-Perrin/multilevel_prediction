#suppressDuplicates("DATA","DATA_FORMATED",TRUE)

print <- FALSE
print <- TRUE
pdf <- TRUE
noTitle <- TRUE

yMax <- 200
xMax <- 30
width = 6.5
height = 5





# MACROSCOPIC MEASUREMENT IN COMPLETE GRAPH

postMeasurement <- c("MACRO_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS")

fileName <- "complete-macro_time"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph",
        var = "TIME", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = NULL, delay = 3, xMin = -0.2, xMax = 7.3, yMax = 1.65, varMax = 200,
        legendPos = "bottomright", noLegend = "ALL", #c("SIZE1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS"),
        noTitle = noTitle, displayBinaryVariable = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement,
        pointList = list("ALL" = c(seq(0,30,10),200)),
        labelList = list("MICRO_MS" = c(seq(0,30,10),200), "MACRO_MS" = seq(10,30,10), "AGENT1_MS" = seq(0,30,10)),
        noLabel = c("EMPTY","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        addLabel = list("AGENT1_MS" = c(1,4,"AGENT"), "MICRO_MS" = c(1,2,"MICRO"), "MACRO_MS" = c(1,4,"MACRO"), "EMPTY" = c(1,3,"EMPTY"), "SIZE2_MS" = c(1,4,"SIZE2"), "SIZE3_MS" = c(1,4,"SIZE3"), "SIZE4_MS" = c(1,4,"SIZE4"), "SIZE5_MS" = c(1,4,"SIZE5"), "SIZE6_MS" = c(1,4,"SIZE6")),
        hide = c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        labelPos = list("MICRO_MS" = c(4,4,3,3,4), "MACRO_MS" = c(4,3,2), "AGENT1_MS" = c(2,2,2,2)),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")




postMeasurement <- c("MACRO_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS")

fileName <- "complete-macro_time-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        var = "TIME", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = NULL, delay = 3,
        xAxis = "TIME", yAxis = "BETA", yMin = 1, yMax = 2.5, xMax = 305, xMin = 0, varMin = 0, varMax = 300, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, boxVarMin = 300, boxMod = c("AGENT1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"), minSizeForNames = 0.05,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")




postMeasurement <- c("MACRO_MS")
preMeasurement <- c("MICRO_MS","MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS")

fileName <- "complete-macro_delay"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", noLegend = TRUE, noTitle = noTitle,
        var = "DELAY", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 100, delay = NULL, varMin = 0, varMax = 200, xMax = 1.13,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement,
        pointList = list("ALL" = c(seq(0,50,10),200)),
        labelList = list("ALL" = c(seq(0,40,10),200), "AGENT1_MS" = c(10,20,30,200)),
        noLabel = c("EMPTY","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        addLabel = list("AGENT1_MS" = c(1,4,"AGENT"), "MICRO_MS" = c(1,2,"MICRO"), "MACRO_MS" = c(1,2,"MACRO"), "EMPTY" = c(1,3,"EMPTY"), "SIZE2_MS" = c(1,2,"SIZE2"), "SIZE3_MS" = c(1,2,"SIZE3"), "SIZE4_MS" = c(1,2,"SIZE4"), "SIZE5_MS" = c(1,2,"SIZE5"), "SIZE6_MS" = c(1,2,"SIZE6")),
        hide = c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  




postMeasurement <- c("MACRO_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS")

fileName <- "complete-macro_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        var = "DELAY", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 100, delay = NULL,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 8, varMax = 200, xMin = 0, varMin = 0, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, boxVarMin = 180, boxMod = c("AGENT1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"), 
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  





# AGENT MEASUREMENT IN COMPLETE GRAPH

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MACRO_MS","AGENT1_MS") #,"SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS","AGENT1_SIZE6_MS","AGENT1_SIZE5_MS","AGENT1_SIZE4_MS","AGENT1_SIZE3_MS","AGENT1_SIZE2_MS")

fileName <- "complete-agent_time"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph",
        var = "TIME", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = NULL, delay = 3, varMax = 200, xMin = -0.15, xMax = 7.3,
        noLegend = TRUE, noTitle = noTitle, displayBinaryVariable = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement,
        pointList = list("ALL" = c(seq(0,50,10),200)),
        labelList = list("MICRO_MS" = c(seq(0,50,10),200), "MACRO_MS" = seq(0,30,10), "AGENT1_MS" = seq(0,50,10), "AGENT1_MACRO_MS" = seq(10,30,10)),
        noLabel = c("EMPTY","AGENT1_MACRO_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS"),
        addLabel = list("AGENT1_MS" = c(1,4,"AGENT"), "MICRO_MS" = c(1,2,"MICRO"), "MACRO_MS" = c(1,4,"MACRO"), "EMPTY" = c(1,3,"EMPTY"), "AGENT1_MACRO_MS" = c(1,4,"  AGENT\nMACRO")), #"SIZE2_MS" = c(1,4,"SIZE2"), "SIZE3_MS" = c(1,4,"SIZE3"), "SIZE4_MS" = c(1,4,"SIZE4"), "SIZE5_MS" = c(1,4,"SIZE5"), "SIZE6_MS" = c(1,4,"SIZE6")),
        hide = c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS"),
        labelPos = list("MICRO_MS" = 4, "MACRO_MS" = 2, "AGENT1_MS" = 2),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")



postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MACRO_MS","AGENT1_MS","AGENT1_SIZE6_MS","AGENT1_SIZE5_MS","AGENT1_SIZE4_MS","AGENT1_SIZE3_MS","AGENT1_SIZE2_MS")

fileName <- "complete-agent_time-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        var = "TIME", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = NULL, delay = 3, yMin = 0, yMax = 40, xMax = 110,
        xAxis = "TIME", yAxis = "BETA", varMin = 0, varMax = 100, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        boxVarMin = 100, boxMod = c("AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS"), minSizeForNames = 2,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")




postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("MICRO_MS","MACRO_MS","AGENT1_MACRO_MS","AGENT1_MS","EMPTY") #,"SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS","AGENT1_SIZE6_MS","AGENT1_SIZE5_MS","AGENT1_SIZE4_MS","AGENT1_SIZE3_MS","AGENT1_SIZE2_MS")

fileName <- "complete-agent_delay"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", noLegend = TRUE, noTitle = noTitle,
        var = "DELAY", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL, varMin = 0, varMax = 200, xMin = -0.15, xMax = 7.8, yMax = 1.05,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement,
        pointList = list("ALL" = c(seq(0,5,1),200)),
        labelList = list("ALL" = c(seq(0,2,1),200)), #, "AGENT1_MS" = c(seq(1,5,1),200)),
        noLabel = c("EMPTY","MACRO_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS"),
        addLabel = list("AGENT1_MS" = c(1,2,"AGENT"), "MICRO_MS" = c(1,2,"MICRO"), "MACRO_MS" = c(1,2,"MACRO"), "EMPTY" = c(1,3,"EMPTY"), "AGENT1_MACRO_MS" = c(1,2,"AGENT\nMACRO")), #, "SIZE2_MS" = c(1,2,"SIZE2"), "SIZE3_MS" = c(1,2,"SIZE3"), "SIZE4_MS" = c(1,2,"SIZE4"), "SIZE5_MS" = c(1,2,"SIZE5"), "SIZE6_MS" = c(1,2,"SIZE6")),
        hide = c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS"),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")




postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","MACRO_MS","AGENT1_MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE2_MS","AGENT1_SIZE6_MS","AGENT1_SIZE2_MS", "SIZE5_MS","SIZE4_MS","SIZE3_MS","AGENT1_SIZE5_MS","AGENT1_SIZE4_MS","AGENT1_SIZE3_MS")

fileName <- "complete-agent_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        var = "DELAY", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        xAxis = "DELAY", yAxis = "BETA", yMin = 1, yMax = 80, varMax = 20, xMin = 0, xMax = 20, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, #boxVarMin = 0, boxMod = c("AGENT1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  






# AGENT MEASUREMENT IN TWO COMMUNITY GRAPH

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "community-agent_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(0.2,0.2), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")


postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "follower-agent_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(0.2,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")


postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "leader-agent_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,0.2), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")


postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "homogeneous-agent_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")



# AGENT MEASUREMENT IN THE TWO COMMUNITY GRAPH (ANIMATION)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

i <- 61
for (v in seq(0,60,1)) {
    r <- v/100
    print(paste("INTERRATE = ",r,sep=""))
    fileName <- paste("animation/2C/frame_",i,sep="")
    
    plotIB (inputFileName = "ANIMATION_2C", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle, unicolorNames = TRUE,
            xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
            suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
            postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
            var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(r,r), contrarian = c(0,0), time = 0, delay = NULL,
            addText = c(as.expression(bquote(rho == .(r)))), addTextX = c(90), addTextY = c(900), addTextCex = c(1.5),
            print = print, pdf = FALSE, width = width*2.2, height = height*2.2, res = 100, outputFileName = fileName, type = "COMPACT_MODEL")
    i <- i-1
}



# AGENT MEASUREMENT IN THE RING

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","NEIGHBORHOOD1_MS","NEIGHBORHOOD2_MS","NEIGHBORHOOD3_MS","NEIGHBORHOOD4_MS","EMPTY","MICRO_MS")

fileName <- "ring-agent_delay-diagram"
plotIB (inputFileName = "FDATA_CHAIN", modelName = "Ring", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle, unicolorNames = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 700, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(9,0), intraRate = c(0,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "RING")



# AGENT MEASUREMENT IN THE CONTRARIAN MODEL

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "contrarian-agent_delay-diagram_transient"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(0.2,0.2), contrarian = c(0.047619,0.047619), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")


fileName <- "contrarian-agent_delay-diagram_stationary"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE, noTitle = noTitle,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 2010, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright", unicolorNames = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(0.2,0.2), contrarian = c(0.047619,0.047619), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")

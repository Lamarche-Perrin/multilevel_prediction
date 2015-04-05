
suppressDuplicates("DATA","ANIMATION_2C")


print <- FALSE
pdf <- FALSE

yMax <- 200
xMax <- 30
width = 24
height = 20


postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

i <- 0
for (v in seq(0,60,1)) {
    r <- v/100
    print(paste("INTERRATE = ",r,sep=""))
    fileName <- paste("animation/2C/frame_",i,sep="")

    plotIB (inputFileName = "ANIMATION_2C", modelName = "Two-community Graph", phaseDiagram = TRUE, noLegend = TRUE,
            xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1000, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
            suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
            postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
            var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(r,r), contrarian = c(0,0), time = 0, delay = NULL,
            print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")
    i <- i+1
}

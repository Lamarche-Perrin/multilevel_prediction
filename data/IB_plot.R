library(RColorBrewer)

print <- FALSE
pdf <- FALSE
am <- FALSE
width = 24
height = 20
xMax <- 100
yMax <- 750
size <- c(10,10)

display <- FALSE
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
        xAxis = "DELAY", yAxis = "BETA", yMax = 200, yMin = 0, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
        postMeasurement = "AGENT1_MS", preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS","SIZE1_MS"), phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = "test", type = "GENERAL_MODEL")  


plotExp <- function (id, r1, r2, display = FALSE, allMeasurements = TRUE, compact = TRUE, contrarian = c(0,0), time = 0) {
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  fileName <- paste("exp.",id,"_param=",round(r1,2),"-",round(r2,2),sep="")
  if (allMeasurements) { fileName <- paste(fileName,"_full",sep="") }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","MACRO_MS","AGENT1_MACRO_MS")
  if (allMeasurements) { measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS") }
    
  measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO2_MS" = c("AGENT","MESO2"), "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO1","MESO2"), "MACRO_MS" = c("MACRO"), "AGENT1_MACRO_MS" = c("AGENT","MACRO"), "AGENT1_MESO1_MS" = c("AGENT","MESO1"), "MESO1_MS" = c("MESO1"), "MESO1_MESO2_MS" = c("MESO1","MESO2"), "MESO2_MS" = c("MESO2"))
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
          xAxis = "DELAY", yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = "AGENT1_MS", preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = "DELAY", size = size, intraRate = c(1,1), interRate = c(r1,r2), contrarian = contrarian, time = time, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}

plotExp(11, 1, 1)
plotExp(12, 2, 2)
plotExp(13, 3, 3)
plotExp(14, 4, 4)
plotExp(15, 5, 5)
plotExp(19, 10, 10)

plotExp(21, 1/1, 1/1)
plotExp(22, 1/2, 1/2)
plotExp(23, 1/3, 1/3)
plotExp(24, 1/4, 1/4)
plotExp(25, 1/5, 1/5)
plotExp(29, 1/10, 1/10)

plotExp(31, 1, 1/1)
plotExp(32, 1, 1/2)
plotExp(33, 1, 1/3)
plotExp(34, 1, 1/4)
plotExp(35, 1, 1/5)
plotExp(39, 1, 1/10)

plotExp(41, 1/1, 1)
plotExp(42, 1/2, 1)
plotExp(43, 1/3, 1)
plotExp(44, 1/4, 1)
plotExp(45, 1/5, 1)
plotExp(49, 1/10, 1)

plotExp(51, 1, 1)
plotExp(52, 2, 1)
plotExp(53, 3, 1)
plotExp(54, 4, 1)
plotExp(55, 5, 1)
plotExp(59, 10, 1)

plotExp(61, 1, 1)
plotExp(62, 1, 2)
plotExp(63, 1, 3)
plotExp(64, 1, 4)
plotExp(65, 1, 5)
plotExp(69, 1, 10)

plotExp(71, 1, 1/1)
plotExp(72, 2, 1/2)
plotExp(73, 3, 1/3)
plotExp(74, 4, 1/4)
plotExp(75, 5, 1/5)
plotExp(79, 10, 1/10)

plotExp(81, 1/1, 1)
plotExp(82, 1/2, 2)
plotExp(83, 1/3, 3)
plotExp(84, 1/4, 4)
plotExp(85, 1/5, 5)
plotExp(89, 1/10, 10)

plotExp(101, 1, 1, contrarian = c(0,0))
plotExp(102, 1, 1, contrarian = c(1/21,1/21))
plotExp(103, 1, 1, contrarian = c(1/21,0))
plotExp(104, 1, 1, contrarian = c(0,1/21))
plotExp(105, 1, 1, contrarian = c(1,1))

plotExp(111, 1, 1, time = -1, contrarian = c(0,0))
plotExp(112, 1, 1, time = -1, contrarian = c(1/21,1/21))
plotExp(113, 1, 1, time = -1, contrarian = c(1/21,0))
plotExp(114, 1, 1, time = -1, contrarian = c(0,1/21))
plotExp(115, 1, 1, time = -1, contrarian = c(1,1))




# COMPARISON CONTRARIAN VS CLASSICAL

plotExp1 <- function (c) {
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES",
          preMeasurement = c("EMPTY","AGENT1_MS","MICRO_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
          var = "TIME", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c, time = NULL, delay = 3,
          labelStep = 10, labelMax = 80, yMax = 1.8,
          print = print, pdf = pdf, width = width, height = height, outputFileName = "macro_c-complete_time")
}

plotExp1(0)
plotExp1(0.001)
plotExp1(0.01)
plotExp1(0.10)



plotExp2 <- function (c, t) {
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE,
          xAxis = "DELAY", yAxis = "BETA", yMax = 200, yMin = 0, varMin = 1, xMax = 40, noNegativeValue = TRUE, noLegend = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
          preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS"), postMeasurement = "AGENT1_MS",
          var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c, time = t, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = "macro_c-complete_delay_diagram")
}

plotExp2(0,0)
plotExp2(0.05,0)
plotExp2(0.10,0)
plotExp2(0.15,0)
plotExp2(0.20,0)


plotExp2(0,-1)
plotExp2(0.05,-1)
plotExp2(0.10,-1)
plotExp2(0.15,-1)
plotExp2(0.20,-1)






plotExp3 <- function (id, r, display = FALSE, allMeasurements = FALSE, compact = TRUE) {
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  fileName <- paste("exp3.",id,"_param=",round(r,2),"-",round(r,2),sep="")
  if (allMeasurements) { fileName <- paste(fileName,"_full",sep="") }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","MACRO_MS","AGENT1_MACRO_MS")
  if (allMeasurements) { measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS") }
  
  measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO2_MS" = c("AGENT","HUB"), "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO","HUB"), "MACRO_MS" = c("MACRO"), "AGENT1_MACRO_MS" = c("AGENT","MACRO"))
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
          xAxis = "DELAY", yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = "AGENT1_MS", preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = "DELAY", size = size, intraRate = c(1,1), interRate = c(r,r), contrarian = 0, time = 0, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}


plotExp3(0, 1, allMeasurements = am)
plotExp3(1, 2, allMeasurements = am)
plotExp3(2, 3, allMeasurements = am)
plotExp3(3, 4, allMeasurements = am)
plotExp3(4, 5, allMeasurements = am)
#plotExp3(5, 10, allMeasurements = am)


plotExp4 <- function (id, r, display = FALSE, allMeasurements = FALSE, compact = TRUE) {
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  
  fileName <- paste("exp4.",id,"_param=",round(r,2),"-",round(r,2),sep="")
  if (compact) { fileName <- paste("c",fileName,sep="") }
  if (allMeasurements) { fileName <- paste(fileName,"_full",sep="") }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MACRO_MS")
  if (allMeasurements) { measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS") }
  
  measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO1_MS" = c("AGENT","MESO"), "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO","HOLE"), "AGENT1_MACRO_MS" = c("AGENT","MACRO"), "MESO1_MS" = c("MESO"), "MESO1_MESO2_MS" = c("MESO","HOLE"), "MACRO_MS" = c("MACRO"))
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
          xAxis = "DELAY", yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = "AGENT1_MS", preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = "DELAY", size = size, intraRate = c(1,1), interRate = c(r,r), contrarian = 0, time = 0, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}


plotExp4(0, 1, allMeasurements = am)
plotExp4(1, 1/2, allMeasurements = am)
plotExp4(2, 1/3, allMeasurements = am)
plotExp4(3, 1/4, allMeasurements = am)
plotExp4(4, 1/5, allMeasurements = am)
#plotExp4(5, 1/10, allMeasurements = am)




plotExp5 <- function (id, r1, r2, display = FALSE, allMeasurements = FALSE, compact = TRUE) {
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  fileName <- paste("exp5.",id,"_param=",round(r1,2),"-",round(r2,2),sep="")
  if (allMeasurements) { fileName <- paste(fileName,"_full",sep="") }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MACRO_MS")
  if (allMeasurements) { measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS") }
  
  measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO1_MS" = c("AGENT","MESO"), "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO","FOLLOWER"), "AGENT1_MACRO_MS" = c("AGENT","MACRO"), "MESO1_MS" = c("MESO"), "MESO1_MESO2_MS" = c("MESO","FOLLOWER"), "MACRO_MS" = c("MACRO"))
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
          xAxis = "DELAY", yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = "AGENT1_MS", preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = "DELAY", size = size, intraRate = c(1,1), interRate = c(r1,r2), contrarian = 0, time = 0, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}

plotExp5(0, 1, 1, allMeasurements = am)
plotExp5(1, 2, 1/2, allMeasurements = am)
plotExp5(2, 3, 1/3, allMeasurements = am)
plotExp5(3, 4, 1/4, allMeasurements = am)
plotExp5(4, 5, 1/5, allMeasurements = am)
#plotExp5(5, 10, 1/10, allMeasurements = am)



plotExp6 <- function (id, r1, r2, display = FALSE, allMeasurements = FALSE, compact = TRUE) {
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  fileName <- paste("exp6.",id,"_param=",round(r1,2),"-",round(r2,2),sep="")
  if (allMeasurements) { fileName <- paste(fileName,"_full",sep="") }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS")
  if (allMeasurements) { measurements <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MACRO_MS") }
  
  measurementText <- list("EMPTY" = c("EMPTY"), "AGENT1_MS" = c("AGENT"), "AGENT1_MESO2_MS" = c("AGENT","LEADER"), "AGENT1_MESO1_MESO2_MS" = c("AGENT","MESO","LEADER"), "AGENT1_MACRO_MS" = c("AGENT","MACRO"), "MESO2_MS" = c("LEADER"), "MESO1_MESO2_MS" = c("MESO","LEADER"), "MACRO_MS" = c("MACRO"))
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "EDGES", phaseDiagram = TRUE, noLegend = !display,
          xAxis = "DELAY", yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = "AGENT1_MS", preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = "DELAY", size = size, intraRate = c(1,1), interRate = c(r1,r2), contrarian = 0, time = 0, delay = NULL,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}


plotExp6(0, 1/1, 1, allMeasurements = am)
plotExp6(1, 1/2, 2, allMeasurements = am)
plotExp6(2, 1/3, 3, allMeasurements = am)
plotExp6(3, 1/4, 4, allMeasurements = am)
plotExp6(4, 1/5, 5, allMeasurements = am)
#plotExp6(5, 1/10, 10, allMeasurements = am)






plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES",
        preMeasurement = c("EMPTY","AGENT1_MS","MICRO_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
        var = "CONTRARIAN", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = NULL, time = -1, delay = 3,
        pointStep = 0.01, labelStep = 0.1,
        print = print, width = width, height = height, outputFileName = "1_macro_cont-complete_contrarian")


plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES", phaseDiagram = TRUE,
        xAxis = "CONTRARIAN", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT1_MS","SIZE_2_MS","SIZE_3_MS","SIZE_4_MS","SIZE_5_MS","SIZE_6_MS","SIZE_7_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
        var = "CONTRARIAN", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = NULL, time = -1, delay = 3,
        noLegend = TRUE, legendPos = "topleft", yMin = 1, yMax = 8, varMin = 0.001, 
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        addText = c("EMPTY","MACRO"), addTextX = c(0.6,0.2), addTextY = c(3,6),
        print = print, width = width, height = height, outputFileName = "2_macro_cont-complete_diagram_contrarian")

plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES", phaseDiagram = TRUE,
        xAxis = "CONTRARIAN", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT1_MS","SIZE_2_MS","SIZE_3_MS","SIZE_4_MS","SIZE_5_MS","SIZE_6_MS","SIZE_7_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
        var = "CONTRARIAN", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = NULL, time = -1, delay = 3,
        noLegend = TRUE, legendPos = "topleft", yMin = 1, yMax = 2.5, varMin = 0.001, xMax = 0.1,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        addText = c("EMPTY","MACRO"), addTextX = c(0.06,0.02), addTextY = c(1.5,2.3),
        print = print, width = width, height = height, outputFileName = "3_macro_cont-complete_diagram_contrarian_zoom")



#plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES",
#        preMeasurement = c("EMPTY","AGENT1_MS","MICRO_MS","MACRO_MS","AGENT1_MACRO_MS"), postMeasurement = "AGENT1_MS",
#       var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = 0.05, time = -1, delay = NULL,
#       print = print, width = width, height = height, outputFileName = "macro_cont-complete_time")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES",
#       preMeasurement = c("EMPTY","AGENT1_MS","MICRO_MS","MACRO_MS","AGENT1_MACRO_MS"), postMeasurement = "AGENT1_MS",
#       var = "CONTRARIAN", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = NULL, time = -1, delay = 3,
#       pointStep = 0.01, labelStep = 0.1,
#       print = print, width = width, height = height, outputFileName = "macro_cont-complete_contrarian")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", update = "NODES", phaseDiagram = TRUE,
#       xAxis = "CONTRARIAN", yAxis = "BETA", preMeasurement = c("EMPTY","AGENT1_MS","MACRO_MS","AGENT1_MACRO_MS"),
#       postMeasurement = "AGENT1_MS",
#       var = "CONTRARIAN", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = NULL, time = -1, delay = 3,
#       suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
#       legendPos = "topleft", yMin = 0, yMax = 1000,
#       print = print, width = width, height = height, outputFileName = "macro_cont-complete_diagram_contrarian")



# STAR MODEL

#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", update = "EDGES",
#       preMeasurement = c("EMPTY","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MICRO_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
#       var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#       print = print, width = width, height = height, outputFileName = "macro_star_time")


plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", update = "EDGES", phaseDiagram = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 130, xMax = 50, varMin = 1, noNegativeValue = TRUE, noLegend = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        preMeasurement = c("EMPTY","AGENT2_MS","AGENT2_MESO1_MS","AGENT2_MACRO_MS","MACRO_MS"), postMeasurement = "AGENT2_MS",
        var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
        addText = c("EMPTY","AGENT","AGENT","CENTER","AGENT","MACRO","MACRO"),
        addTextX = c(35,12,3,3,22,22,34)*1.2, addTextY = c(10,30,100,96,100,96,50),
        print = print, width = width, height = height, outputFileName = "4_agent_star_diagram_delay")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", update = "EDGES", phaseDiagram = TRUE,
#        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 600, xMax = 10, varMin = 1, noNegativeValue = TRUE, noLegend = FALSE,
#       suppressSubPhases = TRUE, legendPos = "topright",
#       preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MESO2_MS","MACRO_MS"), postMeasurement = "AGENT1_MS",
#       var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#       print = print, width = width, height = height, outputFileName = "Center_star_diagram_delay")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", update = "EDGES", phaseDiagram = TRUE,
#        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 30, varMin = 1, noNegativeValue = TRUE, noLegend = FALSE,
#        suppressSubPhases = TRUE,
#        preMeasurement = c("EMPTY","AGENT1_MESO2_MS","MESO2_MS","MACRO_MS"), postMeasurement = "MESO2_MS",
#        var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#        print = print, width = width, height = height, outputFileName = "macro_star_time")

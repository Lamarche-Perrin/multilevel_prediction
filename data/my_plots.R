library(RColorBrewer)

suppressDuplicates("DATA","DATA_AGG")
suppressDuplicates("DATA_CHAIN","FDATA_CHAIN")
#suppressDuplicates("DATA","DATA_MAJ_BINS",TRUE)


fileName <- "output_file"
print <- FALSE
pdf <- FALSE

yMax <- 200
xMax <- 30
width = 24
height = 20


# ring experiment
postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","MICRO_MS","AGENT1_MS","NEIGHBORHOOD1_MS","NEIGHBORHOOD2_MS","NEIGHBORHOOD3_MS")

fileName <- "ring_experiment_size7"
plotIB (inputFileName = "FDATA_CHAIN", modelName = "Ring", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 400, xMax = 40, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(7,0), intraRate = c(0,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "RING")


postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","MICRO_MS","AGENT1_MS","NEIGHBORHOOD1_MS","NEIGHBORHOOD2_MS","NEIGHBORHOOD3_MS","NEIGHBORHOOD4_MS")

fileName <- "ring_experiment_size9"
plotIB (inputFileName = "FDATA_CHAIN", modelName = "Ring", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1000, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(9,0), intraRate = c(0,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "RING")



# two-community tests
postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")

fileName <- "two-community_test"
plotIB (inputFileName = "DATA_F2", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1000, xMax = 100, xMin = 1, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,0.5), interRate = c(1,0.5), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")



# With aggregation

postMeasurement <- c("AGENT1_MS")
#postMeasurement <- c("MACRO_MS")
preMeasurement <- c("MACRO_MS")

fileName <- "coarse-graining"
plotIB (inputFileName = "DATA_AGG", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 120, xMin = 0, xMax = 100, varMin = 0, varStep = 100,
        unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, measurementText = measurementText,
        var = "DELAY", size = c(9,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        withAggregation = TRUE, phasesNames = TRUE, aggregatedNames = TRUE, minSizeForNames = 2,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")


plotIB (inputFileName = "DATA_FORMATED_2", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 8, yMax = 18, xMin = 15, xMax = 51, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        withAggregation = TRUE, phasesNames = TRUE, aggregatedNames = TRUE, onlyPoints = TRUE,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")


#PRELIMINARY
#Prediction of the macro-state in the complete graph (classical in transient) -> time and delay

postMeasurement <- c("MACRO_MS")
preMeasurement <- c("MICRO_MS","EMPTY","AGENT1_MS","MACRO_MS")

fileName <- "complete-macro_classical-transient_time"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", legendPos = "bottomright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, labelList = list("ALL" = c(0,1,10,100)), noLabel = c("EMPTY"),
        var = "TIME", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = NULL, delay = 1, pointList = list("ALL" = c(0,1,10,100)),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")

fileName <- "complete-macro_classical-transient_delay"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", legendPos = "topright", yMax = 1.7, xMax = 9,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, labelList = list("ALL" = c(0,1,10,100)), noLabel = c("EMPTY"),
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL, varMin = 1,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

fileName <- "complete-macro_classical-transient_time-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "TIME", yAxis = "BETA", yMax = 2.3, yMin = 1, xMax = 200, xMin = 0, varMin = 0, varMax = 300, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "TIME", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = NULL, delay = 1,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

fileName <- "complete-macro_classical-transient_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 80, xMax = 100, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 100, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  


#Prediction of the macro-state in the complete graph (contrarian 1/N+1 in transient) -> time and delay

postMeasurement <- c("MACRO_MS")
preMeasurement <- c("MICRO_MS","EMPTY","AGENT1_MS","MACRO_MS")

fileName <- "complete-macro_contrarian-transient_time"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", legendPos = "bottomright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, labelList = list("ALL" = c(0,1,10,100)), noLabel = c("EMPTY"),
        var = "TIME", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = NULL, delay = 1,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

fileName <- "complete-macro_contrarian-transient_delay"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", legendPos = "topright", yMax = 1.7, xMax = 9,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, labelList = list("ALL" = c(0,1,10,100)), noLabel = c("EMPTY"),
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = 0, delay = NULL, varMin = 1,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

fileName <- "complete-macro_contrarian-transient_time-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "TIME", yAxis = "BETA", yMax = 2.2, yMin = 1, xMax = 100, xMin = 0, varMin = 0, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "TIME", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = NULL, delay = 1,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

fileName <- "complete-macro_contrarian-transient_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 80, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  


#Prediction of the macro-state in the complete graph (contrarian 1/N+1 in stationnary)

postMeasurement <- c("MACRO_MS")
preMeasurement <- c("MICRO_MS","SIZE1_MS","EMPTY","MACRO_MS")
fileName <- "macro_contrarian-stationary_delay"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", legendPos = "topright", yMax = 4, xMax = 9,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, labelList = list("ALL" = c(0,1,10,100)), noLabel = c("EMPTY"),
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

preMeasurement <- c("MICRO_MS","SIZE1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS","EMPTY","MACRO_MS")
fileName <- "complete-macro_contrarian-stationary_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 60, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  



#REFERENCE MODEL
#Prediction of one agent in the complete graph (classical in transient)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","MACRO_MS","AGENT1_MACRO_MS")

fileName <- "complete-agent_classical-transient_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 200, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  


#Prediction of one agent in the complete graph (contrarian 1/N+1 in transient)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","MACRO_MS","AGENT1_MACRO_MS")

fileName <- "complete-agent_contrarian-transient_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 200, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  


#Prediction of one agent in the complete graph (contrarian 1/N+1 in stationary)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","MACRO_MS","AGENT1_MACRO_MS")
fileName <- "complete-agent_contrarian-stationary_delay-diagram"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 100, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")  

#Soft transition in the diagram
preMeasurement <- c("AGENT1_MS","EMPTY","MACRO_MS","AGENT1_MACRO_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS",
                    "AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS","AGENT1_SIZE7_MS")
fileName <- "complete-agent_contrarian_stationary_delay-diagram_soft-transitions"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 100, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/9,1/9), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")



#GENERALIZATION OF THE METRIC
#Majority metric in the classical case (transient)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS","AGENT1_MACRO_2B","MACRO_2B")

fileName <- "complete-agent_classical-transient_majority"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1000, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  


#soft transition with the empty measurement
postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS",
                    "AGENT1_MACRO_2B","MACRO_2B","AGENT1_MACRO_3B","MACRO_3B",
                    "AGENT1_MACRO_4B","MACRO_4B","AGENT1_MACRO_6B","MACRO_6B",
                    "AGENT1_MACRO_8B","MACRO_8B","AGENT1_MACRO_12B","MACRO_12B")
fileName <- "complete-agent_classical-transient_majority-bins"
plotIB (inputFileName = "DATA_MAJ_BINS", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 750, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(23,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  


#Several resolutions
postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS","AGENT1_MACRO_MAJ","MACRO_MAJ",
                    #"AGENT1_MACRO_5PC","MACRO_5PC",
                    "AGENT1_MACRO_10PC","MACRO_10PC",
                    "AGENT1_MACRO_50PC","MACRO_50PC","AGENT1_MACRO_90PC","MACRO_90PC")
fileName <- "complete-agent_classical-transient_majority-pc"
plotIB (inputFileName = "DATA_MAJ_BINS", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 750, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(23,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  


#Majority metric in the contrarian case (stationary)

postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS","AGENT1_MACRO_2B","MACRO_2B")

fileName <- "complete-agent_contrarian-stationary_majority"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 1000, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/21,1/21), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  


preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS",
                    "AGENT1_MACRO_2B","MACRO_2B","AGENT1_MACRO_4B","MACRO_4B","AGENT1_MACRO_10B","MACRO_10B")

#soft transition with the empty measurement
fileName <- "complete-agent_contrarian-stationary_majority-bins"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 400, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/21,1/21), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  

#Several resolutions
preMeasurement <- c("AGENT1_MS","EMPTY","AGENT1_MACRO_MS","MACRO_MS",
                    "AGENT1_MACRO_2B","MACRO_2B","AGENT1_MACRO_10PC","MACRO_10PC",
                    "AGENT1_MACRO_20PC","MACRO_20PC","AGENT1_MACRO_30PC","MACRO_30PC",
                    "AGENT1_MACRO_40PC","MACRO_40PC","AGENT1_MACRO_50PC","MACRO_50PC",
                    "AGENT1_MACRO_60PC","MACRO_60PC","AGENT1_MACRO_70PC","MACRO_70PC")
fileName <- "complete-agent_contrarian-stationary_majority_resolutions"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 400, xMin = 0, xMax = 100, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE, legendPos = "topright",
        postMeasurement = postMeasurement, preMeasurement = preMeasurement, phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(10,10), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/21,1/21), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "COMPACT_MODEL")  










display <- FALSE
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
        xAxis = "DELAY", yAxis = "BETA", yMax = 200, yMin = 0, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
        postMeasurement = "AGENT1_MS", preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS","SIZE1_MS"), phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = 0, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = "test", type = "GENERAL_MODEL")  


plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
        xAxis = "DELAY", yAxis = "BETA", yMax = 200, yMin = 0, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
        postMeasurement = "AGENT1_MS", preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS","SIZE1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS"), phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(8,0), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/21,1/21), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = "test", type = "GENERAL_MODEL")  

plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
        xAxis = "DELAY", yAxis = "BETA", yMax = 200, yMin = 0, xMax = 30, xMin = 0, varMin = 1, noNegativeValue = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
        postMeasurement = "AGENT1_MS", preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS","MESO2_MS"), phasesNames = TRUE, measurementText = measurementText,
        var = "DELAY", size = c(4,4), intraRate = c(1,1), interRate = c(1,1), contrarian = c(1/21,1/21), time = -1, delay = NULL,
        print = print, pdf = pdf, width = width, height = height, outputFileName = "test", type = "GENERAL_MODEL")  






time <- -1
contrarian <- c(1/21,1/21)

plotExp(11, 1, 1, communityMeasurements = FALSE, binMeasurements = TRUE, name = "resolution_complete_graph")
plotExp(11, 1, 1, communityMeasurements = FALSE, majMeasurements = TRUE, name = "majority_complete_graph")
plotExp(11, 1, 1, communityMeasurements = FALSE, majMeasurements = TRUE, pcMeasurements = TRUE, name = "other_maj_complete_graph")


plotExp(11, 1, 1, contrarian = contrarian, time = -1)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = -1, size = c(8,0), compact = FALSE)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = NULL, delay = 1, var = "TIME", size = c(8,0), compact = FALSE, postMacro = TRUE, sizeMeasurements = TRUE)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = 100, size = c(8,0), compact = FALSE, postMacro = TRUE, sizeMeasurements = TRUE)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = 0, size = c(8,0), compact = FALSE, postMacro = TRUE, sizeMeasurements = TRUE)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = -1, size = c(8,0), compact = FALSE, postMacro = TRUE, sizeMeasurements = TRUE)
plotExp(11, 1, 1, contrarian = c(1/9,1/9), time = -1, size = c(8,0), compact = FALSE, sizeMeasurements = TRUE)
xplotExp(11, 1, 1, contrarian = c(0,0), time = 0, size = c(8,0), compact = FALSE, sizeMeasurements = TRUE)

plotExp(11, 1, 1, contrarian = contrarian, time = -1)
plotExp(12, 2, 2, contrarian = contrarian, time = -1)
plotExp(13, 3, 3, contrarian = contrarian, time = -1)
plotExp(14, 4, 4, contrarian = contrarian, time = -1)
plotExp(15, 5, 5, contrarian = contrarian, time = -1)
plotExp(19, 10, 10, contrarian = contrarian, time = -1)

plotExp(21, 1/1, 1/1, contrarian = contrarian, time = -1)
plotExp(22, 1/2, 1/2, contrarian = contrarian, time = -1)
plotExp(23, 1/3, 1/3, contrarian = contrarian, time = -1)
plotExp(24, 1/4, 1/4, contrarian = contrarian, time = -1)
plotExp(25, 1/5, 1/5, contrarian = contrarian, time = -1)
plotExp(29, 1/10, 1/10, contrarian = contrarian, time = -1)

plotExp(31, 1, 1/1, contrarian = contrarian, time = -1)
plotExp(32, 1, 1/2, contrarian = contrarian, time = -1)
plotExp(33, 1, 1/3, contrarian = contrarian, time = -1)
plotExp(34, 1, 1/4, contrarian = contrarian, time = -1)
plotExp(35, 1, 1/5, contrarian = contrarian, time = -1)
plotExp(39, 1, 1/10, contrarian = contrarian, time = -1)

plotExp(41, 1/1, 1, contrarian = contrarian, time = -1)
plotExp(42, 1/2, 1, contrarian = contrarian, time = -1)
plotExp(43, 1/3, 1, contrarian = contrarian, time = -1)
plotExp(44, 1/4, 1, contrarian = contrarian, time = -1)
plotExp(45, 1/5, 1, contrarian = contrarian, time = -1)
plotExp(49, 1/10, 1, contrarian = contrarian, time = -1)

plotExp(51, 1, 1, contrarian = contrarian, time = -1)
plotExp(52, 2, 1, contrarian = contrarian, time = -1)
plotExp(53, 3, 1, contrarian = contrarian, time = -1)
plotExp(54, 4, 1, contrarian = contrarian, time = -1)
plotExp(55, 5, 1, contrarian = contrarian, time = -1)
plotExp(59, 10, 1, contrarian = contrarian, time = -1)

plotExp(61, 1, 1, contrarian = contrarian, time = -1)
plotExp(62, 1, 2, contrarian = contrarian, time = -1)
plotExp(63, 1, 3, contrarian = contrarian, time = -1)
plotExp(64, 1, 4, contrarian = contrarian, time = -1)
plotExp(65, 1, 5, contrarian = contrarian, time = -1)
plotExp(69, 1, 10, contrarian = contrarian, time = -1)

plotExp(71, 1, 1/1, contrarian = contrarian, time = -1)
plotExp(72, 2, 1/2, contrarian = contrarian, time = -1)
plotExp(73, 3, 1/3, contrarian = contrarian, time = -1)
plotExp(74, 4, 1/4, contrarian = contrarian, time = -1)
plotExp(75, 5, 1/5, contrarian = contrarian, time = -1)
plotExp(79, 10, 1/10, contrarian = contrarian, time = -1)

plotExp(81, 1/1, 1, contrarian = contrarian, time = -1)
plotExp(82, 1/2, 2, contrarian = contrarian, time = -1)
plotExp(83, 1/3, 3, contrarian = contrarian, time = -1)
plotExp(84, 1/4, 4, contrarian = contrarian, time = -1)
plotExp(85, 1/5, 5, contrarian = contrarian, time = -1)
plotExp(89, 1/10, 10, contrarian = contrarian, time = -1)



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
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph",
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
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE,
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
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
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
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
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
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
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
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
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

#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph",
#       preMeasurement = c("EMPTY","MESO1_MS","MESO2_MS","MESO1_MESO2_MS","MICRO_MS","MACRO_MS"), postMeasurement = "MACRO_MS",
#       var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#       print = print, width = width, height = height, outputFileName = "macro_star_time")


plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", phaseDiagram = TRUE,
        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 130, xMax = 50, varMin = 1, noNegativeValue = TRUE, noLegend = TRUE,
        suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
        preMeasurement = c("EMPTY","AGENT2_MS","AGENT2_MESO1_MS","AGENT2_MACRO_MS","MACRO_MS"), postMeasurement = "AGENT2_MS",
        var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
        addText = c("EMPTY","AGENT","AGENT","CENTER","AGENT","MACRO","MACRO"),
        addTextX = c(35,12,3,3,22,22,34)*1.2, addTextY = c(10,30,100,96,100,96,50),
        print = print, width = width, height = height, outputFileName = "4_agent_star_diagram_delay")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", phaseDiagram = TRUE,
#        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 600, xMax = 10, varMin = 1, noNegativeValue = TRUE, noLegend = FALSE,
#       suppressSubPhases = TRUE, legendPos = "topright",
#       preMeasurement = c("EMPTY","AGENT1_MS","AGENT1_MESO2_MS","MACRO_MS"), postMeasurement = "AGENT1_MS",
#       var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#       print = print, width = width, height = height, outputFileName = "Center_star_diagram_delay")


#plotIB (inputFileName = "DATA_FORMATED", modelName = "Star Graph", phaseDiagram = TRUE,
#        xAxis = "DELAY", yAxis = "BETA", yMin = 0, yMax = 30, varMin = 1, noNegativeValue = TRUE, noLegend = FALSE,
#        suppressSubPhases = TRUE,
#        preMeasurement = c("EMPTY","AGENT1_MESO2_MS","MESO2_MS","MACRO_MS"), postMeasurement = "MESO2_MS",
#        var = "DELAY", size = c(1,9), intraRate = c(0,0), interRate = c(1,1), contrarian = 0, time = 0, delay = NULL,
#        print = print, width = width, height = height, outputFileName = "macro_star_time")



plotExp <- function (id, r1, r2, display = FALSE, compact = TRUE, contrarian = c(0,0), time = 0, name = NULL, size = c(10,10),
                     postMacro = FALSE, var = "DELAY", delay = NULL,
                     communityMeasurements = TRUE, majMeasurements = FALSE, pcMeasurements = FALSE, binMeasurements = FALSE,
                     sizeMeasurements = FALSE) {
  
  if (size[2] == 0) { communityMeasurements = FALSE }
  if (compact) { type <- "COMPACT_MODEL"} else { type <- "GENERAL_MODEL" }
  
  if (!is.null(name)) { fileName <- name }
  else {
    fileName <- paste("exp.",id,"_param=",round(r1,2),"-",round(r2,2),sep="")
    if (!identical(contrarian,c(0,0))) { fileName <- paste("c",fileName,sep="") }
  }
  
  measurements <- c("EMPTY","AGENT1_MS","AGENT1_MACRO_MS","MACRO_MS")  
  if (communityMeasurements) {
    measurements <- c(measurements,c("AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","MESO1_MS","MESO2_MS","MESO1_MESO2_MS"))
  }
  
  if (majMeasurements) { measurements <- c(measurements,c("AGENT1_MACRO_MAJ","MACRO_MAJ")) }
  
  if (sizeMeasurements) {
    measurements <- c(measurements,c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS"))    
    measurements <- c(measurements,c("AGENT1_SIZE2_MS","AGENT1_SIZE3_MS","AGENT1_SIZE4_MS","AGENT1_SIZE5_MS","AGENT1_SIZE6_MS","AGENT1_SIZE7_MS"))    
  }
  
  if (pcMeasurements) {
    measurements <- c(measurements,c("AGENT1_MACRO_10PC","MACRO_10PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_20PC","MACRO_20PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_30PC","MACRO_30PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_40PC","MACRO_40PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_50PC","MACRO_50PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_60PC","MACRO_60PC"))
    measurements <- c(measurements,c("AGENT1_MACRO_70PC","MACRO_70PC"))
    #    measurements <- c(measurements,c("AGENT1_MACRO_80PC","MACRO_80PC"))
    #    measurements <- c(measurements,c("AGENT1_MACRO_90PC","MACRO_90PC"))    
  }
  
  if (binMeasurements) {
    measurements <- c(measurements,c("AGENT1_MACRO_2B","MACRO_2B"))
    measurements <- c(measurements,c("AGENT1_MACRO_4B","MACRO_4B"))
    measurements <- c(measurements,c("AGENT1_MACRO_10B","MACRO_10B"))
    #    measurements <- c(measurements,c("AGENT1_MACRO_20B","MACRO_20B"))
  }
  
  postMeasurement = "AGENT1_MS"
  if (postMacro) { postMeasurement = "MACRO_MS" }
  
  plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph", phaseDiagram = TRUE, noLegend = !display,
          xAxis = var, yAxis = "BETA", yMax = yMax, yMin = 0, xMax = xMax, xMin = 0, varMin = 1, noNegativeValue = TRUE,
          suppressSubPhases = TRUE, suppressInterPhases = !display, unicolor = !display, legendPos = "topright",
          postMeasurement = postMeasurement, preMeasurement = measurements, phasesNames = TRUE, measurementText = measurementText,
          var = var, size = size, intraRate = c(1,1), interRate = c(r1,r2), contrarian = contrarian, time = time, delay = delay,
          print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = type)  
}

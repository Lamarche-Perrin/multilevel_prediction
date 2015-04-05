#suppressDuplicates("DATA","DATA_FORMATED",TRUE)

print <- FALSE
print <- TRUE
pdf <- TRUE
noTitle <- TRUE

yMax <- 200
xMax <- 30
width = 6.5
height = 5



postMeasurement <- c("MACRO_MS")
preMeasurement <- c("EMPTY","MICRO_MS","MACRO_MS","AGENT1_MS","SIZE6_MS","SIZE5_MS","SIZE4_MS","SIZE3_MS","SIZE2_MS")

fileName <- "complete-macro_classical-transient_time"
plotIB (inputFileName = "DATA_FORMATED", modelName = "Complete Graph",
        var = "TIME", size = c(7,0), intraRate = c(1,0), interRate = c(0,0), contrarian = c(0,0), time = NULL, delay = 3, xMin = -0.2, xMax = 7.3, yMax = 1.65,
        legendPos = "bottomright", noLegend = "ALL", #c("SIZE1_MS","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS","SIZE7_MS"),
        noTitle = noTitle, displayBinaryVariable = TRUE,
        postMeasurement = postMeasurement, preMeasurement = preMeasurement,
        pointList = list("ALL" = c(seq(0,30,10),200)),
        labelList = list("MICRO_MS" = seq(0,30,10), "MACRO_MS" = seq(10,30,10), "AGENT1_MS" = seq(0,30,10)),
        noLabel = c("EMPTY","SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        addLabel = list("AGENT1_MS" = c(1,4,"AGENT"), "MICRO_MS" = c(1,2,"MICRO"), "MACRO_MS" = c(1,4,"MACRO"), "EMPTY" = c(1,3,"EMPTY"), "SIZE2_MS" = c(1,4,"SIZE2"), "SIZE3_MS" = c(1,4,"SIZE3"), "SIZE4_MS" = c(1,4,"SIZE4"), "SIZE5_MS" = c(1,4,"SIZE5"), "SIZE6_MS" = c(1,4,"SIZE6")), #"SIZE4_MS" = c(1,4,"S4"), "SIZE5_MS" = c(1,4,"S5"), "SIZE6_MS" = c(1,4,"S6"), "SIZE7_MS" = c(1,4,"S7")),
        hide = c("SIZE2_MS","SIZE3_MS","SIZE4_MS","SIZE5_MS","SIZE6_MS"),
        labelPos = list("MICRO_MS" = c(4,4,3,3), "MACRO_MS" = c(4,3,3), "AGENT1_MS" = c(2,2,2,2)),
        print = print, pdf = pdf, width = width, height = height, outputFileName = fileName, type = "GENERAL_MODEL")


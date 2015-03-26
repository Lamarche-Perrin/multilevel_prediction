library(RColorBrewer)

suppressDuplicates("DATA","DATA_2C")


fileName <- "output_file"
print <- FALSE
pdf <- FALSE

yMax <- 200
xMax <- 30
width = 24
height = 20


N1 <- 10
N2 <- 10

f <- 1/5
b11 <- round(1/(N1*(N1-1)),6)
b22 <- round(1/(N2*(N2-1)),6)
b12 <- round(1/(N1*N2),6)
b21 <- round(1/(N2*N1),6)

s11 <- round(f/(N1*(N1-1)),6)
s22 <- round(f/(N2*(N2-1)),6)
s12 <- round(f/(N1*N2),6)
s21 <- round(f/(N2*N1),6)


# two-community tests
postMeasurement <- c("AGENT1_MS")
preMeasurement <- c("EMPTY","AGENT1_MS","AGENT1_MESO1_MS","AGENT1_MESO2_MS","AGENT1_MESO1_MESO2_MS","AGENT1_MACRO_MS","MESO1_MS","MESO1_MESO2_MS","MESO2_MS","MACRO_MS")


plot2C <- function (fileName, i11, i22, i12, i21) {
    plotIB (inputFileName = "DATA_2C", modelName = "Two-communities", type = "COMPACT_MODEL",
            xAxis = "DELAY", yAxis = "BETA", var = "DELAY", time = 0, delay = NULL,
            size = c(10,10), intraRate = c(i11,i22), interRate = c(i12,i21),
            contrarian = c(0,0),
            postMeasurement = postMeasurement, preMeasurement = preMeasurement,
            varMin = 1, xMin = 1, xMax = 100, yMin = 0, yMax = 3000,
            phaseDiagram = TRUE, noLegend = TRUE, noNegativeValue = TRUE,
            suppressSubPhases = TRUE, suppressInterPhases = TRUE, unicolor = TRUE,
            phasesNames = TRUE, measurementText = measurementText,
            print = print, pdf = pdf, width = width, height = height,
            outputFileName = fileName
            )
}

s <- "0.2"
print <- TRUE
plot2C (paste("exp2C_1.0_1.0_1.0_1.0",sep=""),     b11,b22,b12,b21)
plot2C (paste("exp2C_1.0_1.0_",s,"_",s,sep=""),    b11,b22,s12,s21)
plot2C (paste("exp2C_1.0_1.0_",s,"_1.0",sep=""),   b11,b22,s12,b21)
plot2C (paste("exp2C_1.0_1.0_1.0_",s,sep=""),      b11,b22,b12,s21)
plot2C (paste("exp2C_",s,"_1.0_",s,"_1.0",sep=""), s11,b22,s12,b21)
plot2C (paste("exp2C_1.0_",s,"_1.0_",s,sep=""),    b11,s22,b12,s21)
plot2C (paste("exp2C_",s,"_1.0_1.0_1.0",sep=""),   s11,b22,b12,b21)
plot2C (paste("exp2C_1.0_",s,"_1.0_1.0",sep=""),   b11,s22,b12,b21)

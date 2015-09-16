
data <- read.csv("landuse_flow.csv")

data <- data[data$SIZE>1,]
colnames(data)

plot (data$SIZE, data$HYpY, type="l", log="")
par(new=TRUE)
lines(data$SIZE, data[,2], type="l")

plot (data$SIZE, data[,6]-min(data[,6]), type="l", log="xy")

abline(h=0)

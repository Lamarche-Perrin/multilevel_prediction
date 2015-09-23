
suffix <- "_0.67"

data <- read.csv(paste("landuse_flow",suffix,".csv",sep=""))

data <- data[data$SIZE>1,]
colnames(data)

plot (data$SIZE, data$FLOW, type="l", log="")
plot (data$SIZE, data$HYpY, type="l", log="")
par(new=TRUE)
lines(data$SIZE, data[,2], type="l")

plot (data$SIZE, data[,6]-min(data[,6]), type="l", log="xy")

abline(h=0)






library(latticeExtra)

n <- 30
gamma <- 0.33


x <- seq(0,(n+1)^2-1)
x1 <- x %% (n+1)
x2 <- (x-x1)/(n+1)


data <- read.csv(paste("landuse_dist_",gamma,".csv",sep=""),header=FALSE)

stat <- as.double(strsplit(as.character(data[data$V1 == n & as.character(data$V2) == "STATIONARY","V3"]),split=";")[[1]])
unif <- as.double(strsplit(as.character(data[data$V1 == n & as.character(data$V2) == "UNIFORM","V3"]),split=";")[[1]])


sum(stat)
sum(init)

cloud(stat~x1+x2, panel.3d.cloud=panel.3dbars, col.facet='grey',
      xlim=c(-1,n+1), ylim=c(-1,n+1),
      xbase=0.5, ybase=0.5, scales=list(arrows=FALSE, col=1),
      par.settings = list(axis.line = list(col = "transparent")))

cloud(unif~x1+x2, panel.3d.cloud=panel.3dbars, col.facet='grey',
      xlim=c(-1,n+1), ylim=c(-1,n+1),
      xbase=0.5, ybase=0.5, scales=list(arrows=FALSE, col=1),
      par.settings = list(axis.line = list(col = "transparent")))

#heatmap.2(acast(data, x1~x2, value.var="stat"),dendrogram="none",scale="none",col=)

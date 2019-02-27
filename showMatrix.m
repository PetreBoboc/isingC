latice1 = dlmread('lat1.txt', ' ', 1, 0);

latice2 = dlmread('lat2.txt', ' ', 1, 0);

figure
subplot(2, 1, 1), imshow(latice1)
title('Initial')
subplot(2, 1, 2), imshow(latice2)
title('Final')

dataX = dlmread('x.txt', ' ', 0, 0);
dataY = dlmread('y.txt', ' ', 0, 0);

figure
plot(dataX, dataY)
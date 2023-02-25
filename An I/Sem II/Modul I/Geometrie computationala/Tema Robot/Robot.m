robotBody = [1 1 2 2 1; 1 2 2 1 1];
robotBody = scale(robotBody,1,3);

robotNeck = [1.3 1.3 1.7 1.7 1.3; 6 6.5 6.5 6 6];
robotHead = [1 1 2 2 1; 6.5 7.5 7.5 6.5 6.5];

robotLeftArm = [0 0 1 1 0; 5 5.5 5.5 5 5];
robotLeftHand = rotate(robotLeftArm,-45);
robotLeftHand = translation(robotLeftHand,-4.8,3.2);

robotRightArm = translation(robotLeftArm,2,0);
robotRightHand = rotate(robotRightArm,45);
robotRightHand = translation(robotRightHand,6.2,0.6);

robotLeftLeg = translation(robotRightHand,-2.2,-2.8);
robotLeftFoot = translation(robotLeftLeg,-0.4,-0.7);

robotRightLeg = rotate(robotLeftLeg,-90);
robotRightLeg = translation(robotRightLeg,0.2,4.65);
robotRightFoot = translation(robotRightLeg,0.45,-0.7)

hold on
plot(robotBody(1,:),robotBody(2,:),"k")
fill(robotBody(1,1:end-1),robotBody(2,1:end-1),"b")

plot(robotNeck(1,:),robotNeck(2,:),"k")
fill(robotNeck(1,1:end-1),robotNeck(2,1:end-1),"b")

plot(robotHead(1,:),robotHead(2,:),"k")
fill(robotHead(1,1:end-1),robotHead(2,1:end-1),"b")

plot(robotLeftArm(1,:),robotLeftArm(2,:),"k")
fill(robotLeftArm(1,1:end-1),robotLeftArm(2,1:end-1),"b")

plot(robotLeftHand(1,:),robotLeftHand(2,:),"k")
fill(robotLeftHand(1,1:end-1),robotLeftHand(2,1:end-1),"b")

plot(robotRightArm(1,:),robotRightArm(2,:),"k")
fill(robotRightArm(1,1:end-1),robotRightArm(2,1:end-1),"b")

plot(robotRightHand(1,:),robotRightHand(2,:),"k")
fill(robotRightHand(1,1:end-1),robotRightHand(2,1:end-1),"b")

plot(robotLeftLeg(1,:),robotLeftLeg(2,:),"k")
fill(robotLeftLeg(1,1:end-1),robotLeftLeg(2,1:end-1),"b")

plot(robotLeftFoot(1,:),robotLeftFoot(2,:),"k")
fill(robotLeftFoot(1,1:end-1),robotLeftFoot(2,1:end-1),"b")

plot(robotRightLeg(1,:),robotRightLeg(2,:),"k")
fill(robotRightLeg(1,1:end-1),robotRightLeg(2,1:end-1),"b")

plot(robotRightFoot(1,:),robotRightFoot(2,:),"k")
fill(robotRightFoot(1,1:end-1),robotRightFoot(2,1:end-1),"b")
axis([-3,6,0,9])
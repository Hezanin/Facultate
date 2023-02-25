hold on

% Boat
%M3 = getXY(3);
Boat = M3;
[x3,y3] = drawBezier_cubic(Boat);
%plot(x3,y3,'y','LineWidth',0.2)
fill(x3,y3,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0])
axis([0,1,0,2])

% Ocean
%M = getXY(3);
Ocean = M;
[x1,y1] = drawBezier_cubic(Ocean);
area(x1,y1,'FaceColor',[0 0.4470 0.7410],'EdgeColor',[0.3010 0.7450 0.9330]);
axis([0,1,0,2])


% Boat - Foremast
%M11 = getXY(3);
Boat_ForeMast = M11;
[x11,y11] = drawBezier_cubic(Boat_ForeMast);
fill(x11,y11,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0])
axis([0,1,0,2])


% Boat - Mainsail1
%M12 = getXY(2);
Boat_Mainsail = M12;
[x12,y12] = drawBezier_quad(Boat_Mainsail);
fill(x12,y12,[0.9 0.9 1],'EdgeColor','w')
axis([0,1,0,2])


% Boat - Main Mast
%M13 = getXY(3);
Boat_Mast2 = M13;
[x13,y13] = drawBezier_cubic(Boat_Mast2);
fill(x13,y13,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0])
axis([0,1,0,2])


% Boat - Mainsail2
%M14 = getXY(2);
Boat_Mainsail2 = M14;
[x14,y14] = drawBezier_quad(Boat_Mainsail2);
fill(x14,y14,[0.9 0.9 1],'EdgeColor','w')
axis([0,1,0,2])


% Boat - Crow's Nest
%M15 = getXY(3);
Boat_Nest = M15;
[x15,y15] = drawBezier_cubic(Boat_Nest);
fill(x15,y15,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0]')
axis([0,1,0,2])


% Boat - Mast 1
%M16 = getXY(3);
Mast_1 = M16;
[x16,y16] = drawBezier_cubic(Mast_1);
fill(x16,y16,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0])
axis([0,1,0,2])


% Boat - Mast 2
%M17 = getXY(3);
Mast_2 = M17;
[x17,y17] = drawBezier_cubic(Mast_2);
fill(x17,y17,[0.4 0.1 0.0],'EdgeColor',[0.4 0.1 0.0])
axis([0,1,0,2])


% Boat - InsideRope 1
%p1 = getXY(10);
rope1 = p1;
fMill(rope1)


% Island - Ground
%M2 = getXY(3);
islandGround = M2;
%pick_ground = uisetcolor([1 1 0],'Select a color')
[x2,y2] = drawBezier_cubic(islandGround);
area(x2,y2,'FaceColor',pick_ground,'EdgeColor',pick_ground);
axis([0,1,0,2])


% Island - Rope-Stake
%M5 = getXY(3);
Stake = M5;
[x5,y5] = drawBezier_cubic(Stake);
fill(x5,y5,[0.4 0.3 0.2],'EdgeColor',[0.4 0.3 0.2]);
axis([0,1,0,2])

% Island - Rope
%p = getXY(13);
rope = p;
rope(2,3) = 0.4036;
rope(1,3) = 0.579493;
fMill(rope)

% Island - Tree Trunk
%M4 = getXY(3);
islandTree_Trunk = M4;
[x19,y19] = drawBezier_quad(islandTree_Trunk);
fill(x19,y19,[0.4 0.3 0.2],'EdgeColor',[0.4 0.3 0.2])
axis([0,1,0,2])


% Island - Tree Leaf 1
%M6 = getXY(3);
Leaf1 = M6;
[x6,y6] = drawBezier_cubic(Leaf1);
%pick_leaf_light = uisetcolor([1 1 0],'Select a color')
fill(x6,y6,pick_leaf_light,'EdgeColor',pick_leaf_light)
axis([0,1,0,2])

% Island - Tree Leaf 2
%M7 = getXY(3);
Leaf2 = M7;
[x7,y7] = drawBezier_cubic(Leaf2);
fill(x7,y7,[0.4 0.7 0.3],'EdgeColor',[0.4 0.7 0.3])
axis([0,1,0,2])

% Island - Tree Leaf 3
%M8 = getXY(3);
Leaf3 = M8;
[x8,y8] = drawBezier_cubic(Leaf3);
fill(x8,y8,pick_leaf_light,'EdgeColor',pick_leaf_light)
axis([0,1,0,2])

% Island - Tree Leaf 4
%M9 = getXY(3);
Leaf4 = M9;
[x9,y9] = drawBezier_cubic(Leaf4);
fill(x9,y9,pick_leaf_light,'EdgeColor',pick_leaf_light)
axis([0,1,0,2])

% Island - Tree Leaf 5
%M10 = getXY(3);
Leaf5 = M10;
[x10,y10] = drawBezier_cubic(Leaf5);
fill(x10,y10,pick_leaf_light,'EdgeColor',pick_leaf_light)
axis([0,1,0,2])

% Sky - Bird 1
%Bird_1 = getXY(3)
[bird_coords_1] = drawBezier_casteljau_cubic(Bird_1);

% Sky - Bird 2
%Bird_2 = getXY(3)
[bird_coords_2] = drawBezier_casteljau_cubic(Bird_2);

% Sky - Bird 3
%Bird_3 = getXY(3)
[bird_coords_3] = drawBezier_casteljau_cubic(Bird_3);


% Sky - Sun
%Sun = getXY(3)
sun_fill= drawBezier_casteljau_cubic(Sun);
%pick_sun = uisetcolor([1 1 0],'Select a color')
fill(sun_fill(1,:),sun_fill(2,:),pick_sun,'EdgeColor',pick_sun);
axis([0,1,0,2])




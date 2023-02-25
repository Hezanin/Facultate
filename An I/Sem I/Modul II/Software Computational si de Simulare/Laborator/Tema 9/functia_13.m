function [] = functia_13(raza_baza,raza_varf,nr_nivele,nr_laturi)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

if raza_baza < raza_varf
    aux = raza_baza;
    raza_baza = raza_varf;
    raza_varf = aux;
end
corrective = raza_baza / nr_nivele;
R = [ raza_baza, linspace(raza_baza - 1, raza_varf + corrective, nr_nivele), raza_varf];
N = nr_laturi;

[x,y,z] = cylinder(R,N);
surf(x,y,z);
end
clear all;
close all;
fs=10000;                       %采样频率
t=0:1/fs:0.5;                   %时间
f1=50;                          %有用信号频率
f2=2000;                        %单一噪声频率
%signal1=square(10*pi*t,50);    %50Hz方波测试信号
signal1=sin(2*pi*f1*t);         %50Hz正弦测试信号
signal2=sin(2*pi*f2*t);         %NHz正弦杂波信号
noise = 0.2*rand(1,length(t));  %生成幅值为0.2的高斯噪声
x=signal1 + signal2 + noise;    %叠加有效信号和噪声
subb(1) = subplot(211);         %显示原始波形和噪声叠加波形
plot(x);
hold on;
grid on;
plot(signal1,'r');
        
load('mybutlow.mat');           %导入低通滤波器系数
d = filter(a,b,x);              %使用filter函数对x滤波，结果给d
subb(2) = subplot(212);         %显示滤波后波形
plot(d);
% hold on
% plot(signal1);
grid on;
linkaxes(subb,'x');
dlmwrite('lowpass_input.txt',x,'delimiter', ' ') 

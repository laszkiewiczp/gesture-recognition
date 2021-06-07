attack_data=load('attack.mat');
double_dribble_data=load('double_dribble.mat');
feet_data=load('feet.mat');
line_data=load('line.mat');
lost_data=load('lost.mat');
stop_data=load('stop.mat');
throw_data=load('throw.mat');
two_min_data=load('two_min.mat');
walking_data=load('walking.mat');

n=size(attack_data.attack,1);
m=size(attack_data.attack,2)/3;

baseline=repmat([-66 10 -1017],m,1);
offset=5;
end_window=10;
%baseline=0;

attack=cell(n,1);
double_dribble=cell(n,1);
feet=cell(n,1);
line=cell(n,1);
lost=cell(n,1);
stop=cell(n,1);
throw=cell(n,1);
two_min=cell(n,1);
walking=cell(n,1);

attack_features=cell(n,1);
double_dribble_features=cell(n,1);
feet_features=cell(n,1);
line_features=cell(n,1);
lost_features=cell(n,1);
stop_features=cell(n,1);
throw_features=cell(n,1);
two_min_features=cell(n,1);
walking_features=cell(n,1);

for i=1:n
    [attack{i},attack_features{i}]=convert_data(attack_data.attack(i,:),baseline,offset,end_window);
    [double_dribble{i},double_dribble_features{i}]=convert_data(double_dribble_data.double_dribble(i,:),baseline,offset,end_window);
    [feet{i},feet_features{i}]=convert_data(feet_data.feet(i,:),baseline,offset,end_window);
    [line{i},line_features{i}]=convert_data(line_data.line(i,:),baseline,offset,end_window);
    [lost{i},lost_features{i}]=convert_data(lost_data.lost(i,:),baseline,offset,end_window);
    [stop{i},stop_features{i}]=convert_data(stop_data.stop(i,:),baseline,offset,end_window);
    [throw{i},throw_features{i}]=convert_data(throw_data.throw(i,:),baseline,offset,end_window);
    [two_min{i},two_min_features{i}]=convert_data(two_min_data.two_min(i,:),baseline,offset,end_window);
    [walking{i},walking_features{i}]=convert_data(walking_data.walking(i,:),baseline,offset,end_window);
end

close all;
figure(1);
subplot(3,1,1);
hold on;
subplot(3,1,2);
hold on;
subplot(3,1,3);
hold on;
for i=1:n
    subplot(3,1,1);
    plot(attack{i}(:,1),'r');
    plot(double_dribble{i}(:,1),'b');
    plot(feet{i}(:,1),'g');
    plot(line{i}(:,1),'k');
    plot(lost{i}(:,1),'m');
    plot(stop{i}(:,1),'y');
    plot(throw{i}(:,1),'c');
    plot(two_min{i}(:,1),'color',[0.5 0.5 0.5]);
    plot(walking{i}(:,1),'color',[0.25 0.75 0.25]);
    subplot(3,1,2);
    plot(attack{i}(:,2),'r');
    plot(double_dribble{i}(:,2),'b');
    plot(feet{i}(:,1),'g');
    plot(line{i}(:,2),'k');
    plot(lost{i}(:,2),'m');
    plot(stop{i}(:,2),'y');
    plot(throw{i}(:,2),'c');
    plot(two_min{i}(:,2),'color',[0.5 0.5 0.5]);
    plot(walking{i}(:,2),'color',[0.25 0.75 0.25]);
    subplot(3,1,3);
    plot(attack{i}(:,3),'r');
    plot(double_dribble{i}(:,3),'b');
    plot(feet{i}(:,3),'g');
    plot(line{i}(:,3),'k');
    plot(lost{i}(:,3),'m');
    plot(stop{i}(:,3),'y');
    plot(throw{i}(:,3),'c');
    plot(two_min{i}(:,3),'color',[0.5 0.5 0.5]);
    plot(walking{i}(:,3),'color',[0.25 0.75 0.25]);
end
hold on;

figure(2);
subplot(3,1,1);
hold on;
subplot(3,1,2);
hold on;
subplot(3,1,3);
hold on;
for i=1:n
    subplot(3,1,1);
    plot(diff(attack{i}(:,1)),'r');
    plot(diff(double_dribble{i}(:,1)),'b');
    plot(diff(feet{i}(:,1)),'g');
    plot(diff(line{i}(:,1)),'k');
    plot(diff(lost{i}(:,1)),'m');
    plot(diff(stop{i}(:,1)),'y');
    plot(diff(throw{i}(:,1)),'c');
    plot(diff(two_min{i}(:,1)),'color',[0.5 0.5 0.5]);
    plot(diff(walking{i}(:,1)),'color',[0.25 0.75 0.25]);
    subplot(3,1,2);
    plot(diff(attack{i}(:,2)),'r');
    plot(diff(double_dribble{i}(:,2)),'b');
    plot(diff(feet{i}(:,2)),'g');
    plot(diff(line{i}(:,2)),'k');
    plot(diff(lost{i}(:,2)),'m');
    plot(diff(stop{i}(:,2)),'y');
    plot(diff(throw{i}(:,2)),'c');
    plot(diff(two_min{i}(:,2)),'color',[0.5 0.5 0.5]);
    plot(diff(walking{i}(:,2)),'color',[0.25 0.75 0.25]);
    subplot(3,1,3);
    plot(diff(attack{i}(:,3)),'r');
    plot(diff(double_dribble{i}(:,3)),'b');
    plot(diff(feet{i}(:,3)),'g');
    plot(diff(line{i}(:,3)),'k');
    plot(diff(lost{i}(:,3)),'m');
    plot(diff(stop{i}(:,3)),'y');
    plot(diff(throw{i}(:,3)),'c');
    plot(diff(two_min{i}(:,3)),'color',[0.5 0.5 0.5]);
    plot(diff(walking{i}(:,3)),'color',[0.25 0.75 0.25]);
end
hold on;

figure(3);
hold on;
for i=1:n
    plot(1:length(attack_features{i}),attack_features{i},'ro');
    plot(1:length(double_dribble_features{i}),double_dribble_features{i},'bo');
    plot(1:length(feet_features{i}),feet_features{i},'go');
    plot(1:length(line_features{i}),line_features{i},'ko');
    plot(1:length(lost_features{i}),lost_features{i},'mo');
    plot(1:length(stop_features{i}),stop_features{i},'yo');
    plot(1:length(throw_features{i}),throw_features{i},'co');
    plot(1:length(two_min_features{i}),two_min_features{i},'o','color',[0.5 0.5 0.5]);
    plot(1:length(walking_features{i}),walking_features{i},'o','color',[0.25 0.75 0.25]);
end


Fattack=zeros(n,length(attack_features{1}));
Fdouble_dribble=zeros(n,length(double_dribble_features{1}));
Ffeet=zeros(n,length(feet_features{1}));
Fline=zeros(n,length(line_features{1}));
Flost=zeros(n,length(lost_features{1}));
Fstop=zeros(n,length(stop_features{1}));
Fthrow=zeros(n,length(throw_features{1}));
Ftwo_min=zeros(n,length(two_min_features{1}));
Fwalking=zeros(n,length(walking_features{1}));

for i=1:n
    Fattack(i,:)=attack_features{i};
    Fdouble_dribble(i,:)=double_dribble_features{i};
    Ffeet(i,:)=feet_features{i};
    Fline(i,:)=line_features{i};
    Flost(i,:)=lost_features{i};
    Fstop(i,:)=stop_features{i};
    Fthrow(i,:)=throw_features{i};
    Ftwo_min(i,:)=two_min_features{i};
    Fwalking(i,:)=walking_features{i};
    end

csvwrite('attack_features.csv',Fattack);
csvwrite('double_dribble_features.csv',Fdouble_dribble);
csvwrite('feet_features.csv',Ffeet);
csvwrite('line_features.csv',Fline);
csvwrite('lost_features.csv',Flost);
csvwrite('stop_features.csv',Fstop);
csvwrite('throw_features.csv',Fthrow);
csvwrite('two_min_features.csv',Ftwo_min);
csvwrite('walking_features.csv',Fwalking);


function [out_data,out_data_features]=convert_data(in_data,baseline,offset,end_window)
    out_data=reshape(table2array(in_data),3,numel(in_data)/3)'+baseline;
    dout_data=diff(out_data);
    %
    endx=round(mean(out_data(end-end_window:end,1)));
    endy=round(mean(out_data(end-end_window:end,2)));
    endz=round(mean(out_data(end-end_window:end,3)));
    maxx=max(out_data(offset:end,1));
    maxy=max(out_data(offset:end,2));
    maxz=max(out_data(offset:end,3));
    minx=min(out_data(offset:end,1));
    miny=min(out_data(offset:end,2));
    minz=min(out_data(offset:end,3));
    
    maxdx=max(dout_data(offset:end,1));
    maxdy=max(dout_data(offset:end,2));
    maxdz=max(dout_data(offset:end,3));
    mindx=min(dout_data(offset:end,1));
    mindy=min(dout_data(offset:end,2));
    mindz=min(dout_data(offset:end,3));
    out_data_features=[endx endy endz maxx maxy maxz minx miny minz maxdx maxdy maxdz mindx mindy mindz];
%     x=out_data(:,1);
%     y=out_data(:,2);
%     z=out_data(:,3);
%     out_data(:,1)=out_data(:,1)./sqrt(x.^2+y.^2+z.^2);
%     out_data(:,2)=out_data(:,2)./sqrt(x.^2+y.^2+z.^2);
%     out_data(:,3)=out_data(:,3)./sqrt(x.^2+y.^2+z.^2);
%     out_data(:,1)=unwrap(atan2(y,z));
%     out_data(:,2)=unwrap(atan2(z,x));
%     out_data(:,3)=asin(z./sqrt(x.^2+y.^2+z.^2));
end
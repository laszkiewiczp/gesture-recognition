steal_data=load('steal.mat');
stop_data=load('stop.mat');
two_min_data=load('two_min.mat');

n=size(steal_data.steal,1);
m=size(steal_data.steal,2)/3;

baseline=repmat([-66 10 -1017],m,1);
offset=5;
end_window=10;
%baseline=0;

steal=cell(n,1);
stop=cell(n,1);
two_min=cell(n,1);

steal_features=cell(n,1);
stop_features=cell(n,1);
two_min_features=cell(n,1);

for i=1:n
    [steal{i},steal_features{i}]=convert_data(steal_data.steal(i,:),baseline,offset,end_window);
    [stop{i},stop_features{i}]=convert_data(stop_data.stop(i,:),baseline,offset,end_window);
    [two_min{i},two_min_features{i}]=convert_data(two_min_data.two_min(i,:),baseline,offset,end_window);
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
    plot(steal{i}(:,1),'r');
    plot(stop{i}(:,1),'b');
    plot(two_min{i}(:,1),'g');
    subplot(3,1,2);
    plot(steal{i}(:,2),'r');
    plot(stop{i}(:,2),'b');
    plot(two_min{i}(:,2),'g');
    subplot(3,1,3);
    plot(steal{i}(:,3),'r');
    plot(stop{i}(:,3),'b');
    plot(two_min{i}(:,3),'g');
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
    plot(diff(steal{i}(:,1)),'r');
    plot(diff(stop{i}(:,1)),'b');
    plot(diff(two_min{i}(:,1)),'g');
    subplot(3,1,2);
    plot(diff(steal{i}(:,2)),'r');
    plot(diff(stop{i}(:,2)),'b');
    plot(diff(two_min{i}(:,2)),'g');
    subplot(3,1,3);
    plot(diff(steal{i}(:,3)),'r');
    plot(diff(stop{i}(:,3)),'b');
    plot(diff(two_min{i}(:,3)),'g');
end
hold on;

figure(3);
hold on;
for i=1:n
    plot(1:length(steal_features{i}),steal_features{i},'ro');
    plot(1:length(stop_features{i}),stop_features{i},'bo');
    plot(1:length(two_min_features{i}),two_min_features{i},'go');
end

Fsteal=zeros(n,length(steal_features{1}));
Fstop=zeros(n,length(stop_features{1}));
Ftwo_min=zeros(n,length(two_min_features{1}));

for i=1:n
    Fsteal(i,:)=steal_features{i};
    Fstop(i,:)=stop_features{i};
    Ftwo_min(i,:)=two_min_features{i};
end

csvwrite('steal_features.csv',Fsteal);
csvwrite('stop_features.csv',Fstop);
csvwrite('two_min_features.csv',Ftwo_min);

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
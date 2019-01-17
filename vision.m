name=imaqhwinfo;
info=imaqhwinfo('winvideo');
id=info.DeviceInfo.DeviceID;
formats=info.DeviceInfo.SupportedFormats;
resolution=char(formats);
vid=videoinput('winvideo',1);
%%%%
set(vid, 'FramesPerTrigger', Inf);
set(vid, 'ReturnedColorspace', 'rgb')
vid.FrameGrabInterval = 5;
start(vid)
c='r';
v=[];
i=1;
j=1;
while(1)    
    %Toma snapshots
    data = getsnapshot(vid);
    diff_im = imsubtract(data(:,:,1), rgb2gray(data));
    %Use a median filter to filter out noise
    diff_im = medfilt2(diff_im, [3 3]);
    % Convert the resulting grayscale image into a binary image.
    diff_im = im2bw(diff_im,0.18);    
    % Remove all those pixels less than 300px
    diff_im = bwareaopen(diff_im,300);    
    % Label all the connected components in the image.
    bw = bwlabel(diff_im, 8);    
    % Here we do the image blob analysis.
    % We get a set of properties for each labeled region.
    stats = regionprops(bw, 'BoundingBox', 'Centroid');    
    % Display the image
    imshow(data)    
    hold on    
    c='w';
    %This is a loop to bound the red objects in a rectangular box.
    for object = 1:length(stats)
        bb = stats(object).BoundingBox;
        bc = stats(object).Centroid;
        rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
        plot(bc(1),bc(2), '-m+')
        a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2)))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
         if round(bc(2))>350
        c='k';        
        else
            if round(bc(2))<200
                c='w';
            else
                c='m';
            end
         end
        
         v(i)=round(bc(2));
         i=i+1;
    end
    rectangle('Position',[0,450,300,400],'FaceColor',c,'LineWidth',2)
    hold off
end
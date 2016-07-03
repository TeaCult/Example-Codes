axesObjs = get(h, 'Children');  %axes handles
dataObjs = get(axesObjs, 'Children'); %handles to low-level graphics objects in axes   
objTypes = get(dataObjs, 'Type');  %type of low-level graphics object 
bearing3 = get(dataObjs, 'YData');
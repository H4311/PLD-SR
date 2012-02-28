function ProportionalColor(value, minVal, maxVal, colorsArray, nbMeasures) {
	var coef = (value-minVal)/(maxVal-minVal);
	var step = 1/(colorsArray.length-1);
	var num = Math.floor(coef/step);
	var remainder = coef/step - num;
	var color = {
		red : Math.floor((colorsArray[num+1].red-colorsArray[num].red)*remainder+colorsArray[num].red),
		green : Math.floor((colorsArray[num+1].green-colorsArray[num].green)*remainder+colorsArray[num].green),
		blue : Math.floor((colorsArray[num+1].blue-colorsArray[num].blue)*remainder+colorsArray[num].blue)
	};
	return color;	
}

function drawGradient(canvas, minVal, maxVal, colorsArray, nbMeasures, unit, text) {
	var ctx = canvas.getContext('2d');  

	// Drawing the grad :
	var lingrad = ctx.createLinearGradient(0,0,0,canvas.height);
	var step = 1/(colorsArray.length-1);
	var l = colorsArray.length-1;
	for (var i = 0; i < colorsArray.length; i++) {
		lingrad.addColorStop(i*step, 'rgb('+colorsArray[l-i].red+', '+colorsArray[l-i].green+','+colorsArray[l-i].blue+')');  
	}
	var style = ctx.fillStyle;
	ctx.fillStyle = lingrad;
	fillRoundCornerRect(ctx, 0, 0,canvas.width,canvas.height,10);
	ctx.fillStyle = style;
	strokeRoundCornerRect(ctx, 0, 0,canvas.width,canvas.height,10);
	
	// Drawing the text :
	var val = 0;
	var text;
	step = canvas.height/(nbMeasures-1);
	for (var i = 1; i < nbMeasures-1; i++) {
		ctx.beginPath();
		ctx.moveTo(0, i*step);  
		ctx.lineTo(3,i*step);  
		ctx.stroke(); 
		val = Math.round((nbMeasures-1-i)*(maxVal-minVal)/(nbMeasures-1)+minVal);
		text = val+unit;
		ctx.fillText(text, (canvas.width/2)-text.length*3, i*step);
		ctx.beginPath();
		ctx.moveTo(canvas.width-3, i*step);  
		ctx.lineTo(canvas.width,i*step);  
		ctx.stroke(); 
	}
}

function strokeRoundCornerRect(ctx, x, y, w, h, r) {
	ctx.beginPath();
	ctx.moveTo(x+r, y);
	ctx.lineTo(x+w-r, y);
	ctx.quadraticCurveTo(x+w, y, x+w, y+r);
	ctx.lineTo(x+w, y+h-r);
	ctx.quadraticCurveTo(x+w, y+h, x+w-r, y+h);
	ctx.lineTo(x+r, y+h);
	ctx.quadraticCurveTo(x, y+h, x, y+h-r);
	ctx.lineTo(x, y+r);
	ctx.quadraticCurveTo(x, y, x+r, y);
	ctx.stroke();
}

function fillRoundCornerRect(ctx, x, y, w, h, r) {
	ctx.beginPath();
	ctx.moveTo(x+r, y);
	ctx.lineTo(x+w-r, y);
	ctx.quadraticCurveTo(x+w, y, x+w, y+r);
	ctx.lineTo(x+w, y+h-r);
	ctx.quadraticCurveTo(x+w, y+h, x+w-r, y+h);
	ctx.lineTo(x+r, y+h);
	ctx.quadraticCurveTo(x, y+h, x, y+h-r);
	ctx.lineTo(x, y+r);
	ctx.quadraticCurveTo(x, y, x+r, y);
	ctx.fill();
}

function drawCircle(ctx, x, y, radius, color) {
	var style = ctx.fillStyle;
	ctx.fillStyle = color;
	ctx.beginPath();  
	ctx.arc(x,y,radius,0,Math.PI*2,true); // Outer circle  
	ctx.closePath();
	ctx.fill();
	ctx.fillStyle = style;
		
}

function drawExclame(ctx, x, y, radius, color) {
	var style = ctx.fillStyle;
	ctx.fillStyle = color;
	ctx.beginPath();  
	ctx.arc(x,y+radius/2,radius/4,0,Math.PI*2,true); // Outer circle  
	ctx.fill();
	
	ctx.beginPath();
	ctx.moveTo(x-radius/4, y-radius*0.75);
	ctx.lineTo(x+radius/4, y-radius*0.75);
	ctx.quadraticCurveTo(x+radius/4+2, y-radius*0.75, x+radius/6, y+radius/6);
	ctx.quadraticCurveTo(x, y+radius/10, x-radius/6, y+radius/6);
	ctx.quadraticCurveTo(x-radius/4-2, y-radius*0.75, x-radius/4, y-radius*0.75);
	ctx.closePath();
	ctx.fill();
	ctx.fillStyle = style;	
}
var STEP = 0;
var TMP;
var TMP0;
var TMPBOXNUM = 5;
var TMPNUM;
var nowNum;
var whoWin = 3;
var myBox1 = [0,0,0,0,0,0,0,0,0];
var myBox2 = [0,0,0,0,0,0,0,0,0];
var myBox3 = [0,0,0,0,0,0,0,0,0];
var myBox4 = [0,0,0,0,0,0,0,0,0];
var myBox5 = [0,0,0,0,0,0,0,0,0];
var myBox6 = [0,0,0,0,0,0,0,0,0];
var myBox7 = [0,0,0,0,0,0,0,0,0];
var myBox8 = [0,0,0,0,0,0,0,0,0];
var myBox9 = [0,0,0,0,0,0,0,0,0];
var bigBox = [0,0,0,0,0,0,0,0,0];
function fresh(){
    var ping = window.localStorage.getItem("ping");
    var chacha = window.localStorage.getItem("chacha");
    var quanquan = window.localStorage.getItem("quanquan");
    var times = window.localStorage.getItem("times");
    var pretimes = window.localStorage.getItem("pretimes");
    document.getElementById("ping").innerHTML = ping;
    document.getElementById("chacha").innerHTML = chacha;
    document.getElementById("quanquan").innerHTML = quanquan;
    var alltimes = parseFloat(ping) + parseFloat(quanquan) + parseFloat(chacha);
    var quanrate = parseFloat(quanquan) / alltimes * 100.0;
    var charate = parseFloat(chacha) / alltimes * 100.0;
    var pingrate = parseFloat(ping) / alltimes * 100.0;
    document.getElementById("pingrate").innerHTML = "平局概率:" + pingrate + "%";
    document.getElementById("quanrate").innerHTML = "先手胜概率:" + quanrate + "%";
    document.getElementById("charate").innerHTML = "后手胜概率:" + charate + "%";
    document.getElementById("alreadyTimes").innerHTML = "总进行局数：" + window.localStorage.getItem("alreadyTimes");
    var myDate = new Date();
    var startTime = window.localStorage.getItem("usingTime");
    var perTime = (Number(myDate.getTime()) - Number(startTime)) / Number(times) / 1000.0;
    document.getElementById("usingTime").innerHTML = "运算速率：" + perTime + "秒/次";
    var lasttimes = Number(pretimes) - Number(times);
    document.getElementById("lasttimes").innerHTML ="剩余循环：" + lasttimes + "次" + "(" + times + "/" + pretimes + ")";
    if(Number(times) < Number(pretimes)){
    	doAll();
   		}
}
//狂下不止
function setTimes(){
    var myDate = new Date();
    var times = prompt("输入循环次数","");
    window.localStorage.setItem("pretimes",times);
    window.localStorage.setItem("times",0);    
    var storeTime = myDate.getTime();
    window.localStorage.setItem("usingTime",storeTime);
    doAll();
}
function doAll(){   	 
     while(whoWin != 0&&whoWin != 1&&whoWin != 2){
      	randomStep();
      }
     if(whoWin == 0||whoWin == 1||whoWin == 2){
         var nowTimes = window.localStorage.getItem("times");
         nowTimes = Number(nowTimes) + 1;
         window.localStorage.setItem("times",nowTimes);
         var alreadyTimes = window.localStorage.getItem("alreadyTimes");
    	 alreadyTimes = Number(alreadyTimes) + 1;
    	 window.localStorage.setItem("alreadyTimes",alreadyTimes);
         window.location = "index.html";
         }
}
//乱下一步
function randomStep(){
    if(whoWin == 0||whoWin == 1||whoWin == 2){
        window.location = "index.html";
        }
    var btnArray = new Array();
    if(STEP == 0){
        for(var i = 1;i <= 9;i ++){
            btnArray.push(5 + " " + i);
            }
        }
    for(var i = 1;i <= 9;i ++){
        for(var n = 1;n <=9;n ++){
            if(document.getElementById("box" + i).style.border == "2px solid red"){
            	if(document.getElementById("box" + i + " btn1")){
            		if(document.getElementById("box" + i + " btn" + n).value != "checked" && document.getElementById("box" + i + " btn" + n).value != "oncecheck"){
                   		btnArray.push(i + " " + n);
                		}
                    }
                }
            }
        }
    //alert(btnArray);
    var ranNum = Math.floor(Math.random() * btnArray.length);    
    var boxDo = btnArray[ranNum];
    var theBoxArray = boxDo.split(" ");
    var theBoxNum = theBoxArray[0];
    var theBox = "box" + theBoxNum;
    var theBtn = "box" + theBoxNum + " btn" + boxDo.slice(2);
    putOn(theBox,theBtn);
    
}
function putOn(box,btn){
    var btnNum = btn.slice(8);
    var boxNum = box.slice(3);
    //点到刚下的格子
    if(document.getElementById(btn).value == "checked"){
        if(confirm("确定悔棋吗？")){
            document.getElementById(btn).innerHTML = "";
            document.getElementById(btn).value = "";
            document.getElementById(btn).style.background = "";
            document.getElementById("box1").style.border = "2px solid black";
    		document.getElementById("box2").style.border = "2px solid black";
    		document.getElementById("box3").style.border = "2px solid black";
    		document.getElementById("box4").style.border = "2px solid black";
    		document.getElementById("box5").style.border = "2px solid black";
    		document.getElementById("box6").style.border = "2px solid black";
    		document.getElementById("box7").style.border = "2px solid black";
    		document.getElementById("box8").style.border = "2px solid black";
    		document.getElementById("box9").style.border = "2px solid black";
            document.getElementById("box" + btnNum).style.border = "solid 2px black";
            document.getElementById("box" + TMPBOXNUM).style.border = "solid 2px red";
            var allBox = [myBox1,myBox2,myBox3,myBox4,myBox5,myBox6,myBox7,myBox8,myBox9];
            allBox[boxNum -1][btnNum - 1] = 0;
            if(TMP0){
                TMP0.value="checked";
                TMP0.style.background = "rgba(240,220,220,0.9)";                
                }           
            STEP --;
            }
        }
        
    else if(STEP == 0 && boxNum != 5){
        return false;
        }
    else if(document.getElementById("box" + boxNum).style.border != "2px solid red" && STEP != 0){
        return false;
        }
    //点到不是刚下的已下棋格子
    else if(document.getElementById(btn).value == "oncecheck"){
        return false;
        }
    //若没有下过这个格子
    else{
        STEP ++;        
        if(STEP % 2 == 0){
            document.getElementById(btn).innerHTML = "☓";
            }
		else{
            document.getElementById(btn).innerHTML = "〇";
            }
        if(TMP != null && TMP != ""){
        	TMP.style.background = "";
            TMP.value = "oncecheck";
            if(TMP0){
            	TMP0.style.background = "";
            	TMP0.value = "oncecheck";
            	}
            if(TMP && TMP != document.getElementById(btn)){
            	TMP0 = TMP;
                document.getElementById("box" + TMPBOXNUM).style.border = "solid 2px black";
                TMPBOXNUM = TMPNUM;
            	}
            TMP = document.getElementById(btn);
            TMPNUM = btnNum;
        	}
        else if(TMP == document.getElementById(btn)){
            TMP.style.background = "rgba(240,220,220,0.9)";
            }
        else{
        	TMP = document.getElementById(btn);
            TMPNUM = btnNum;
        	} 
    	document.getElementById(btn).value = "checked";        
        document.getElementById(btn).style.background = "rgba(240,220,220,0.9)";   
        NOWNUM = btnNum;                  
        checkWin(boxNum,btnNum);
        checkNext(boxNum,btnNum);
        if(whoWin != 1&&whoWin != 2){
        	checkPing();
            }
		}    
   	
}
//找出下一个棋子应下在哪儿
function checkNext(boxNum,btnNum){      
    document.getElementById("box" + TMPBOXNUM).style.border = "solid 2px black";
    document.getElementById("box1").style.border = "2px solid black";
    document.getElementById("box2").style.border = "2px solid black";
    document.getElementById("box3").style.border = "2px solid black";
    document.getElementById("box4").style.border = "2px solid black";
    document.getElementById("box5").style.border = "2px solid black";
    document.getElementById("box6").style.border = "2px solid black";
    document.getElementById("box7").style.border = "2px solid black";
    document.getElementById("box8").style.border = "2px solid black";
    document.getElementById("box9").style.border = "2px solid black";
    document.getElementById("box" + btnNum).style.border = "solid 2px red";
    if(document.getElementById("box" + btnNum).value == "already"){
        document.getElementById("box1").style.border = "2px solid red";
        document.getElementById("box2").style.border = "2px solid red";
        document.getElementById("box3").style.border = "2px solid red";
        document.getElementById("box4").style.border = "2px solid red";
        document.getElementById("box5").style.border = "2px solid red";
        document.getElementById("box6").style.border = "2px solid red";
        document.getElementById("box7").style.border = "2px solid red";
        document.getElementById("box8").style.border = "2px solid red";
        document.getElementById("box9").style.border = "2px solid red";
        document.getElementById("box" + btnNum).style.border = "2px solid black";
        }
}

function checkWin(boxNum,btnNum){
    if(whoWin == 0||whoWin == 1||whoWin ==2){
        return false;
        }
    var allBox = [myBox1,myBox2,myBox3,myBox4,myBox5,myBox6,myBox7,myBox8,myBox9];
    if(STEP % 2 == 0){
        allBox[boxNum -1][btnNum - 1] = 1;
        }
    else{
        allBox[boxNum -1][btnNum - 1] = -1;
        }
   
    var thisBox = allBox[boxNum - 1];
    if(thisBox[0] + thisBox[1] + thisBox[2] == 3 || thisBox[3] + thisBox[4] + thisBox[5] == 3 || thisBox[6] + thisBox[7] + thisBox[8] == 3 || thisBox[0] + thisBox[3] + thisBox[6] == 3 || thisBox[1] + thisBox[4] + thisBox[7] == 3 || thisBox[2] + thisBox[5] + thisBox[8] == 3 || thisBox[0] + thisBox[4] + thisBox[8] == 3 || thisBox[2] + thisBox[4] + thisBox[6] == 3){
        document.getElementById("box" + boxNum).innerHTML = "☓";
        document.getElementById("box" + boxNum).style.fontSize = "190px";
        document.getElementById("box" + boxNum).value = "already";
        bigBox[boxNum - 1] = 1;
        }
    else if(thisBox[0] + thisBox[1] + thisBox[2] == -3 || thisBox[3] + thisBox[4] + thisBox[5] == -3 || thisBox[6] + thisBox[7] + thisBox[8] == -3 || thisBox[0] + thisBox[3] + thisBox[6] == -3 || thisBox[1] + thisBox[4] + thisBox[7] == -3 || thisBox[2] + thisBox[5] + thisBox[8] == -3 || thisBox[0] + thisBox[4] + thisBox[8] == -3 || thisBox[2] + thisBox[4] + thisBox[6] == -3){
        document.getElementById("box" + boxNum).innerHTML = "〇";
        document.getElementById("box" + boxNum).style.fontSize = "190px";
        document.getElementById("box" + boxNum).value = "already";
        bigBox[boxNum - 1] = -1;
        } 
     
    if(bigBox[0] + bigBox[1] + bigBox[2] == -3 || bigBox[3] + bigBox[4] + bigBox[5] == -3 || bigBox[6] + bigBox[7] + bigBox[8] == -3 || bigBox[0] + bigBox[3] + bigBox[6] == -3 || bigBox[1] + bigBox[4] + bigBox[7] == -3 || bigBox[2] + bigBox[5] + bigBox[8] == -3 || bigBox[0] + bigBox[4] + bigBox[8] == -3 || bigBox[2] + bigBox[4] + bigBox[6] == -3){
        for(var i = 0;i < 9;i ++){
            if(bigBox[i] == -1){
                var n = i + 1;
                var col1 = Math.random() * 255;
                var col2 = Math.random() * 255;
                var col3 = Math.random() * 255;
                document.getElementById("box" + n).style.background = "rgba(" + col1 + "," + col2 + "," + col3 + ",0.8)";
                }
            }
        whoWin = 1;
        record();
        document.getElementById("whowin").innerHTML = "恭喜圈圈获胜！";
        //alert("恭喜圈圈获胜！");
        return false;
        }
    else if(bigBox[0] + bigBox[1] + bigBox[2] == 3 || bigBox[3] + bigBox[4] + bigBox[5] == 3 || bigBox[6] + bigBox[7] + bigBox[8] == 3 || bigBox[0] + bigBox[3] + bigBox[6] == 3 || bigBox[1] + bigBox[4] + bigBox[7] == 3 || bigBox[2] + bigBox[5] + bigBox[8] == 3 || bigBox[0] + bigBox[4] + bigBox[8] == 3 || bigBox[2] + bigBox[4] + bigBox[6] == 3){
        for(var i = 0;i < 9;i ++){
            if(bigBox[i] == 1){
                var n = i + 1;
                var col1 = Math.random() * 255;
                var col2 = Math.random() * 255;
                var col3 = Math.random() * 255;
                document.getElementById("box" + n).style.background = "rgba(" + col1 + "," + col2 + "," + col3 + ",0.8)";
                }
            }
        whoWin = 2;
        record();
        document.getElementById("whowin").innerHTML = "恭喜叉叉获胜！";
        //alert("恭喜叉叉获胜！");
        return false;
        }
}
function record(){
    if(!window.localStorage.getItem("chacha") || !window.localStorage.getItem("quanquan") ||!window.localStorage.getItem("ping")){
        window.localStorage.setItem("chacha",0);
        window.localStorage.setItem("quanquan",0);
        window.localStorage.setItem("ping",0);        
        }
    else if(whoWin == 0){
        var num = window.localStorage.getItem("ping");
        num = Number(num) + 1;
        window.localStorage.setItem("ping",num);
        }
    else if(whoWin == 1){
        var num = window.localStorage.getItem("quanquan");
        num = Number(num) + 1;
        window.localStorage.setItem("quanquan",num);
        }
    else if(whoWin == 2){
        var num = window.localStorage.getItem("chacha");
        num = Number(num) + 1;
        window.localStorage.setItem("chacha",num);
        }
}
function checkPing(){
    var btnArray = [];
    if(STEP == 0){
        for(var i = 1;i <= 9;i ++){
            btnArray.push(5 + " " + i);
            }
        }
    for(var i = 1;i <= 9;i ++){
        for(var n = 1;n <=9;n ++){
            if(document.getElementById("box" + i).style.border == "2px solid red"){
            	if(document.getElementById("box" + i + " btn1")){
            		if(document.getElementById("box" + i + " btn" + n).value != "checked" && document.getElementById("box" + i + " btn" + n).value != "oncecheck"){
                   		btnArray.push(i + " " + n);
                		}
                    }
                }
            }
        }
   if(btnArray.length < 1){
        whoWin = 0;
        record();
        document.getElementById("whowin").innerHTML = "平局！";
        //alert("打平了！");
        return false;
        }
}
function clearIt(){
    if(confirm("是否清除数据？（清除后无法恢复）")){
    window.localStorage.clear();
    window.localStorage.setItem("ping",0);
    window.localStorage.setItem("quanquan",0);
    window.localStorage.setItem("chacha",0);
    window.localStorage.setItem("alreadytimes",0);
    window.location = 'index.html';
    }
}
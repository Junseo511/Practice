import ddf.minim.*; 
AudioPlayer player; 
AudioPlayer clearplay;
AudioPlayer failplay;
Minim minim;
Minim clear;
Minim fail;
PImage background;
int a=0; int b=0; int c=0;
int aa=0; int bb=0; int cc=0;
int t=0; int tt=0;
float r; float rr=0;
float N = 150;
int k=0;
int combo=0;
int time=0;
int score=0;
int bR=50; int bG=70; int bB=245;
float ml=0; float md=0; float mr=0;
float KCL = 0;
float KCD = 0;
float KCR = 0;
boolean GO =false;
String GCM = "";


//DW

void ok1()
{
  if (270<=a&&a<=315 ||270<=aa&&aa<=315)
  {
    combo+=1;score=score+100*combo+time/4;
  }
  else
  combo=0;
}

void ok2()
{
  if (270<=b&&b<=315 || 270<=bb&&bb<=315)
    {
      combo+=1;score=score+100*combo+time/4;
    }
    else
    combo=0;
}

void ok3()
{
  if (270<=c&&c<=315||270<=cc&&cc<=315)
    {
      combo+=1;score=score+100*combo+time/4;
    }
    else
    combo=0;
}


//DS

void setup()
{
  size(800,450);
  noLoop();
  background = loadImage("background.jpg");
  minim = new Minim(this); 
  player = minim.loadFile("BGM.mp3"); 
  player.play(); 
}

void draw()
{
  frameRate(150);
  strokeWeight(3);
  background(0);
  image(background,0,0);
  image(background,0,0,800,450);
  fill(0);
  noStroke();
  rect(79,0,303,340);
  strokeWeight(3);
  stroke(255);
  line(180,0,180,340);
  line(280,0,280,340);
  stroke(230);
  strokeWeight(1.6);
  
  t+=1;
  if(t==64)
  {
    t=0; r=random(1,5);
  }
  
  if(2<=r&&r<3)
  {
    fill(255,70,70,190);
    rect(79,a,100,14);
    a+=5;
  }
  
  if(3<=r&&r<4)
  {
    fill(70,255,70,190);
    rect(180,b,100,14);
    b+=5;
  }
  
  if(4<=r&&r<5)
  {
    fill(70,70,255,190);
    rect(281,c,100,14);
    c+=5;
  }
  
  if (a==320)
  {
    a=0;
  }
  
  if (b==320)
  {
    b=0;
  }
  
  if (c==320)
  {
    c=0;
  }
 
  k+=1;
  
  if(k>=32)
  {
    tt+=1;
  }
  
  if(tt==64)
  {
    tt=0;
    rr=random(1,5);
  }
  
  if(2<=rr&&rr<3)
  {
    fill(255,70,70,190);
    rect(79,aa,100,14);
    aa+=5;
  }
  
  if(3<=rr&&rr<4)
  {
    fill(70,255,70,190);
    rect(180,bb,100,14);
    bb+=5;
  }
  
  if(4<=rr&&rr<5)
  {
    fill(70,70,255,190);
    rect(281,cc,100,14);
    cc+=5;
  }
  
  if (aa==320)
  {
    aa=0;
  }
  
  if (bb==320)
  {
  bb=0;
  }
  
  if (cc==320)
  {
  cc=0;
  }
  
  //R
  noStroke();
  fill(20,30,180,200);
  rect(79,305,303,5);
  
  //SR
  fill(255,180);
  stroke(0);
  strokeWeight(5);
  strokeJoin(BEVEL);
  rect(555,295,200,60);
 
  //GSB
  noStroke();
  fill(bR,bG,bB);
  rect(430,80,100,50,8,8,8,8);
  fill(255);
  textSize(28);
  text("START",435,115);
  if(GO==true){bR=50; bG=70; bB=245; loop();}

  noStroke();
  fill(0);
  ellipse(630,100,140,140);
  fill(0+time*51/600,255-time*51/600,70);
  arc(630,100,137,137,radians(0.12*time-90),radians(270));
  noStroke();
 
  if(time==3000)
  {
    time=0;
    noLoop();
  }
  
  //CB
  textAlign(CENTER);
  fill(111,128,255,150+40*sin(radians(N)));
  N=N+15;
  textSize(70);
  text(combo,230,120);
  fill(0);
  
  //SB
  textSize(40);
  textAlign(CENTER);
  text(score/10,656,340);
  textAlign(LEFT);
  time=time+1;
  
  //KB
  stroke(255);
  strokeWeight(3);
  fill(KCL,100);
  rect(78,348,101,95);
  fill(KCD,100);
  rect(179,348,101,95);
  fill(KCR,100);
  rect(280,348,101,95);
  fill(255,200);
  textSize(20);
  text("LEFT",106,403);text("DOWN",198,403);text("RIGHT",301,403);
  
  //BL
  fill(255,70,70,ml); rect(80,0,100,340);
  fill(70,255,70,md); rect(180,0,100,340);
  fill(70,70,255,mr); rect(280,0,100,340);
 
  textAlign(CENTER);
  fill(237,121,255);
  textSize(45);
  text(GCM,400,220);
  fill(8,255,212);
  textSize(46);
  text(GCM,400,240);
  fill(255,124,23);
  textSize(47);
  text(GCM,400,260);
  textAlign(LEFT);
  
  //GC
  if((score>=80000)&&(time==3000))
  {
  GCM = "Great! You did a good job!";
  clear = new Minim(this); 
  clearplay = minim.loadFile("clear.wav"); 
  clearplay.play(); 
  }
  if((score<80000)&&(time==3000))
  {
  GCM = "Try again!";
  fail = new Minim(this); 
  failplay = minim.loadFile("fail.wav"); 
  failplay.play(); 
  }
}

void keyPressed()
{
  if(keyCode==LEFT)
  {
    ok1();
    KCL=180;
    ml=100;
  }
  if(keyCode==DOWN)
  {
    ok2();
    KCD=180;
    md=100;
  }
  if(keyCode==RIGHT)
  {
    ok3();
    KCR=180;
    mr=100;
  }
}

void keyReleased()
{
  KCL=0;KCD=0;KCR=0;ml=0;md=0;mr=0;
}

void mousePressed()
{
  if(GO==true)
    {
     redraw();score=0;combo=0; bR=0; bG=20; bB=220; player.rewind(); player.play();
    }
}

void mouseReleased()
{
  bR=0;bG=20;bB=220;
}

void mouseDragged()
{
  GS();
}

void mouseMoved()
{
  GS();
}

void GS()
{
  if (mouseX > 430 && mouseX < 530 && 
  mouseY > 80 && mouseY <130){GO=true;GCM="";}else{GO=false;}
}

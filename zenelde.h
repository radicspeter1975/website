<!DOCTYPE html>
<html lang="hu">
<!-- 24.11.23 html -->
<head>
	<title>tesztszerverem.hu</title>
	<meta charset="utf-8">
    <meta name="description" content="Radics Péter tesztszervere">
    <meta name="keywords" content="Topikutya zenélde klippek kották névnap képek virágok programok">
    <meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="icon" type="image/x-icon" href="/favicon.ico">
	<link rel="apple-touch-icon" href="/favicon.png">
	<link rel="stylesheet" href="/back/css/w3.css">
	<link rel="stylesheet" href="/back/css/media.css">
	<script src="/back/js/alap.js"></script>
	<script src="/back/zenelde/zenelde.js?2025032316"></script>
	<style>
 pre { 
      text-align: left; 
      /* background: whitesmoke; */
      white-space: pre-wrap;
      word-break: break-all;
    }
</style>
</head>

<body class="w3-content">

<header class="w3-green">
    <h6><a href="/" class="w3-btn w3-hover-gray">kezdőlap</a></h6>
</header>

<!-- main -->
<main class="w3-container w3-center">
    <!-- 2024.11.23 lasten-"w3-image" -->
<h4 class="w3-blue w3-padding-small">
    <label for="kertext">zenélde</label>
    <input class="w3-margin w3-round" id="kertext" type="text" size="25" placeholder="kereső, -: minden, véletlen dal" onkeyup="keres()">
    <button class="w3-button w3-yellow w3-hover-red w3-round-large w3-medium w3-padding-small" onclick="lasten()">új dalok</button>
    <button class="w3-button w3-yellow w3-hover-red w3-round-large w3-medium w3-padding-small" onclick="dal('vel')">véletlen dal</button>
    <button class="w3-button w3-yellow w3-hover-red w3-round-large w3-medium w3-padding-small" id="favours" onclick="favourites()" disabled>kedvencek</button>
    <button class="w3-button w3-red w3-hover-yellow w3-round-large w3-medium w3-padding-small" id="favbutton" title="add/remove favourites" onclick="addremfav()" disabled>+</button>
</h4>
<div id="htartalom">
  post lekérése ...
</div>

<script>
//24.09.03  window.history.replaceState...;
// peti_fetch_fv az alap.js-ben

"use strict";

// storage vars
const storagearray = [];
let storageready = false;

const sortcollator = new Intl.Collator('hu', { numeric: true, sensitivity: 'base' });
// html vars
const favbtn = document.getElementById('favbutton');
const hely = document.getElementById('htartalom');

const phppath = "/back/php/zenelde_b.php?post=";
let postname="akt";

// -------------------fgv-k----------------------

function kiir(tartalom){
  hely.innerHTML+=tartalom; // title hamarabb
  document.getElementById("kertext").value="";
  document.title=document.getElementById("ptitle").innerHTML;
  window.history.replaceState(null, document.title, "/link/zenelde");

  document.getElementById("kertext").blur();
  if(storageready) updatefavbtn();
}

function dal(mit){
    let videoid, webcim, title;
    
    switch (mit) {
      case 'vel':
        let i=Math.floor(Math.random() * darab);
        [videoid, webcim, title] = listaT[i];
        break;
      case 'akt':
        [videoid, webcim, title] = indexT[19];
        break;
      default:
        let sor = listaT.findIndex((element) => element[1] == mit);
        if(sor!=-1) [videoid, webcim, title] = listaT[sor];
        else [videoid, webcim, title] = indexT[19];
     }

    // title sorok
    let videolink=`<a id="currentlink" data-favour="${webcim+title}" target="_blank" href="https://www.youtube.com/watch?v=${videoid}">${webcim}</a>`;
    hely.innerHTML= `<h4 class="w3-teal"><a id="ptitle" href="/link/zenelde?${webcim}">${title}</a> ${videolink}</h4><br>`;
    
    // tobbi
    peti_fetch_fv(phppath + webcim, kiir);
}

function keres(){
//const listaT = [ ["I9gU3L0J2ks", "2008-08-08", "K's Choice - Everything for free"], ...
    const mitk = document.getElementById("kertext").value.toUpperCase();

    document.title="keresés";
    window.history.replaceState(null, document.title, "/link/zenelde");
    favbtn.disabled=true;
    let talalat=0;
    let sorok="";

    if(mitk.length>0)
    {
     for (let i = 0; i < darab ; i++) 
     {
        let egylink = listaT[i][1];
        let egytitle = listaT[i][2];
        if(egytitle.toUpperCase().indexOf(mitk) > -1)
          {
              sorok+= '<a class="w3-hover-red" id="' + egylink +'" href="#" onclick="dal(this.id);return false;">' + egytitle  +'</a><br>';
              talalat++;
          }
     }
     switch(talalat) {
      case 0:
        hely.innerHTML="<b>erre nincs találat</b>";
        break;
      case 1:
        dal(sorok.substr(28,10));
        break;
      default:
        hely.innerHTML="<b>" + talalat + " találat: </b><br>" + sorok;
     }

    }
    else
     { 
        let i=Math.floor(Math.random() * darab);
        let egylink = listaT[i][1];
        let egytitle = listaT[i][2];
        hely.innerHTML="<b>keress valamire ... vagy nézd meg ezt:</b><br>" 
        hely.innerHTML+= '<a class="w3-hover-red" id="' + egylink +'" href="#" onclick="dal(this.id);return false;">' + egylink + " "+ egytitle  +'</a><br><br>' ;
     }
}

function lasten(){
// indexT-ben az utolso 20

    document.title="új dalok";
    window.history.replaceState(null, document.title, "/link/zenelde");

    favbtn.disabled=true;
    let sorok="";
    for (let i = 19; i >= 0 ; i--) 
     {
        const egylink = indexT[i][1];
        const egytitle = indexT[i][2];
        sorok+= '<a class="w3-hover-red" id="' + egylink +'" href="#" onclick="dal(this.id);return false;">' + egylink + " "+ egytitle +'<br>';
        sorok+= `<img class="w3-image" src="https://img.youtube.com/vi/${indexT[i][0]}/mqdefault.jpg" alt="youtube preview"></a><br><br>`;
        
     }
     hely.innerHTML="<b>utolsó 20 dal:</b><br>" + sorok;
}

function addremfav(){
 // aktualis dal hozza vagy el, storage es array update!
 
 let aktualiscim = document.getElementById("currentlink").dataset.favour;
 if(storagearray.includes(aktualiscim)){
     // torolni
     storagearray.splice(storagearray.indexOf(aktualiscim), 1);
 }
 else  {
     
    storagearray.push(aktualiscim);
    storagearray.sort((a, b) => { return sortcollator.compare(a.substr(10), b.substr(10)); });

/*
storagearray.sort (
    function (a, b) {
        if ( a.substr(10) === b.substr(10)) {
            return 0;
        } else {
            return (a.substr(10) < b.substr(10)) ? -1 : 1;
        }
    }
    );
*/

 }
 
 localStorage.setItem('favourites',storagearray.join('|'));
 updatefavbtn();
}

function delfav(melyik){
     storagearray.splice(storagearray.indexOf(melyik), 1);
     favourites();
}


function favourites(){
 // kedvenc lista kep+link? + egesz törlése addelement button?
    let sorok;
    document.title="kedvencek";
    window.history.replaceState(null, document.title, "/link/zenelde");
    favbtn.disabled=true;
    
    if(storageready){
       sorok = "<b>mentett kedvenceid:</b><br>";
       for (const egysor of storagearray)
          {
            const egylink = egysor.substring(0,10);
            const egytitle = egysor.substr(10);
            sorok+= '<a class="w3-hover-red" id="' + egylink +'" href="#" onclick="dal(this.id);return false;">' + egytitle  +'</a> ';
            sorok+= `<button id="${egysor}" class="w3-button w3-red w3-hover-yellow w3-round-large w3-medium w3-padding-small" onclick="delfav(this.id)">-</button><br>`;
          }
        if(storagearray.length) sorok+='<br><button class="w3-button w3-red w3-hover-yellow w3-round-large w3-medium w3-padding-small" onclick="clearallfav()">összes kedvenc törlése</button><br><br>';   
    }
    else 
    {
       sorok="<b>itt lehetnének a kedvenceid, ha a localStorage engedélyezett lenne...</b><br>";
    }
    hely.innerHTML=sorok;
  
}

function clearallfav(){
    if (window.confirm('tényleg töröljem mind?'))
    {
      localStorage.setItem('favourites','');
      storagearray.length = 0;
      favourites();
    }

}

function updatefavbtn(){
    // favbtn allapotanak +/- meghatarozasa
    let aktualiscim = document.getElementById("currentlink").dataset.favour;
    favbtn.disabled=false;
    if(storagearray.includes(aktualiscim)) favbtn.innerHTML='-';
    else favbtn.innerHTML='+';
}

//-------------------------------
// start:

//setup storage
(function() 
{
  try {
    let storagestring = localStorage.getItem('favourites');
    storageready = true;
    document.getElementById("favours").disabled = false;
    document.getElementById("favbutton").disabled = false;
    
    if(storagestring === null)
    {
      localStorage.setItem('favourites','');
    }
    else 
    {
      if(storagestring) storagearray.push(...storagestring.split('|'));
      }
  } catch (error) {
    alert('cookie/localStorage nincs engedélyezve');
  };
}
());

// utolso 20 bejegyzes helye
const darab=listaT.length;
const indexT=listaT.slice(listaT.length-20);

//start
(function() 
{
// abc szerint rendezes a keresohoz
listaT.sort((a, b) => { return sortcollator.compare(a[2], b[2]); });

/* listaT.sort (
    function (a, b) {
        if (a[2] === b[2]) {
            return 0;
        } else {
            return (a[2] < b[2]) ? -1 : 1;
        }
    }
); */

// gyorslinkek
if(postname.substr(0,1)=='?') //search or links
{
    let keresendo=postname.substr(1);
    document.getElementById("kertext").value=keresendo.replace('+',' ');
    keres();
}
else {
    switch (postname) {
      case 'uto':
        lasten();
        break;
      case 'fav':
        favourites();
        break;        
      case 'vel':
      case 'akt':
      default:
        dal(postname);
     } 
    }
}
());

</script></main>

<footer class="w3-container w3-green w3-center">
    2025.03.23. <a class="w3-hover-black" target="_blank" href="/link/nevnap"> Emőke</a> napja van.
    Kapcsolat:&nbsp;<a class="w3-hover-black" href="/cdn-cgi/l/email-protection#ddbcb9b0b4b39da9b8aea7a9aea7b8afabb8afb8b0f3b5a8e2aea8bfb7b8bea9e0a9b8aea7a9aea7b8afabb8afb8b0f3b5a8">Radics&nbsp;Péter</a> 
</footer>

<script data-cfasync="false" src="/cdn-cgi/scripts/5c5dd728/cloudflare-static/email-decode.min.js"></script></body>

</html>
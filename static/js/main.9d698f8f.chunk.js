(window.webpackJsonpsquarepair=window.webpackJsonpsquarepair||[]).push([[0],[,,,,,function(e,t,n){e.exports=n(16)},,,,,function(e,t,n){},function(e,t,n){},function(e,t,n){},function(e,t,n){},function(e,t,n){},function(e,t,n){},function(e,t,n){"use strict";n.r(t);var a=n(0),r=n.n(a),c=n(4),o=n.n(c),l=(n(10),n(1)),u=n(2);n(11),n(12),n(13);var i=Object(a.memo)((function(e){var t=e.color,n=e.onClick;return r.a.createElement("div",{className:"tile",style:{background:t},onClick:function(){return n()}})}));var m=Object(a.memo)((function(e){var t=e.row,n=e.rowNumber,a=e.onClick;return r.a.createElement("div",{className:"tile-row-wrapper"},t.map((function(e,t){return r.a.createElement(i,{color:e,onClick:function(){return a(n,t)},key:t})})))}));n(14);var f=Object(a.memo)((function(e){var t=e.text,n=e.onClick,a=e.style;return r.a.createElement("div",{className:"styled-button",style:a,onClick:function(){return n()}},t)}));function s(e,t,n,a){for(var r=[],c=0;c<t;c++)r.push(n);for(var o=[],l=0;l<e;l++)o.push([].concat(r));a([o])}function p(e,t,n){var a=n.indexOf(e);return n[(a+1)%t]}function b(e,t,n,a,r,c){var o=Object(l.a)(n),u=o[0].length,i=o.length;o[e][t]=p(o[e][t],a,r);for(var m=-1;m<3;m+=2)e+m>=0&&e+m<i&&(o[e+m][t]=p(o[e+m][t],a,r)),t+m>=0&&t+m<u&&(o[e][t+m]=p(o[e][t+m],a,r));c(o)}function v(e,t,n){for(var a=!0,r=e[0][0],c=0;c<t&&a;c++)for(var o=0;o<n&&a;o++)a=r===e[c][o];return a}var d=Object(a.memo)((function(){var e=Object(a.useState)([[]]),t=Object(u.a)(e,2),n=t[0],c=t[1],o=Object(a.useState)(!1),i=Object(u.a)(o,2),p=i[0],d=i[1],E=Object(a.useState)(3),h=Object(u.a)(E,2),j=h[0],O=h[1],w=Object(a.useState)(3),g=Object(u.a)(w,2),C=g[0],k=g[1],N=Object(a.useState)(3),y=Object(u.a)(N,2),x=y[0],S=y[1],F=n[n.length-1].map((function(e){return Object(l.a)(e)})),D=[["#CE3141","#31CEBE"],["#7800ff","#FF7800","#00FF78"],["#66D926","#26BFD9","#9926D9","#D94026"]][x-2];function M(e){var t=[].concat(Object(l.a)(n),[e]);c(t)}function B(e,t){b(e,t,F,x,D,M),v(F,j,C)&&(d(!0),setTimeout((function(){return d(!1)}),1e3))}function R(){!function(e,t){if(e.length-1>0){var n=e;n.pop(),t(Object(l.a)(n))}}(n,c)}function q(){!function e(t,n,a,r,c,o,u,i){for(var m=n.map((function(e){return Object(l.a)(e)})),f=0;f<t;f++){b(Math.floor(Math.random()*a),Math.floor(Math.random()*r),m,o,u,i)}v(n,a,r)&&e(t,m,a,r,c,o,u,i),i(m)}(arguments.length>0&&void 0!==arguments[0]?arguments[0]:20,F,j,C,n,x,D,M)}return Object(a.useEffect)((function(){s(j,C,D[0],c)}),[C,j,x,p]),r.a.createElement("div",{className:"board-wrapper"},r.a.createElement("div",{className:"control-wrapper"},r.a.createElement(f,{text:p?"You did it!":"Shuffle",onClick:function(){return q()}}),r.a.createElement(f,{text:"Undo",onClick:function(){return R()}}),r.a.createElement(f,{text:"Reset",onClick:function(){s(j,C,D[0],c)}}),r.a.createElement("div",{className:"input-wrapper"},r.a.createElement("label",null,"Rows:",r.a.createElement("input",{placeholder:"Rows",value:j,onChange:function(e){return function(e){O(e)}(e.target.value)},type:"number",min:"2",max:"10"})),r.a.createElement("label",null,"Columns:"," ",r.a.createElement("input",{placeholder:"Columns",value:C,onChange:function(e){return function(e){k(e)}(e.target.value)},type:"number",min:"2",max:"10"})),r.a.createElement("label",null,"Colors:",r.a.createElement("input",{placeholder:"Colors",value:x,onChange:function(e){return function(e){S(e)}(e.target.value)},type:"number",min:"2",max:"4"})))),r.a.createElement("div",{className:"board ".concat(p?"bg-green":"")},F.map((function(e,t){return r.a.createElement(m,{rowNumber:t,row:e,onClick:B,key:t})}))))}));n(15);var E=Object(a.memo)((function(){return r.a.createElement("div",{className:"instruction-wrapper"},r.a.createElement("h2",{className:"instruction-header"},"How to Play"),r.a.createElement("ul",{className:"rules"},r.a.createElement("li",null,"The goal of the game is to match the colors of all tiles"),r.a.createElement("li",null,"Click on each tile and the adjacent ones to change color"),r.a.createElement("li",null,"Each change in color is following a determined order based on the amount of chosen colors")))}));var h=Object(a.memo)((function(){return r.a.createElement("div",{className:"app-wrapper"},r.a.createElement(d,null)," ",r.a.createElement(E,null))}));o.a.render(r.a.createElement(h,null),document.getElementById("root"))}],[[5,1,2]]]);
//# sourceMappingURL=main.9d698f8f.chunk.js.map
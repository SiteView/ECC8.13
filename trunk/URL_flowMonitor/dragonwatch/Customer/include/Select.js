
function clearcofield(){
        if (document.frmEdit.cokeyword.value == "输入公司关键字")
               document.frmEdit.cokeyword.value = "";
}
function clearfunfield(){
       if (document.frmEdit.funkeyword.value == "输入职位关键字")
               document.frmEdit.funkeyword.value = "";
}
function clearotherfield(){
       if (document.frmEdit.otherkeyword.value == "输入其他关键字")
               document.frmEdit.otherkeyword.value = "";
}

var psid="";

function DoLoad(form,funtypev){
        var n;
        var i,j,k;
        var num;
        num= GetObjID('funtype[]');
        num1= GetObjID('funtypeca');

//        for(n = 1; n < po_ca_show.length+1; n++){
//                NewOptionName = new Option(po_ca_show[n-1], po_ca_value[n-1]);
//                form.d_position1.options[n] = NewOptionName;
//        }
//        NewOptionName = new Option('ll','ll');
//        form.elements[num].options[0] = NewOptionName;
//        for(n = 0; n < po_detail_value[0].length; n++){
//                NewOptionName = new Option(po_detail_show[0][n], po_detail_value[0][n]);
//                form.elements[num1].options[n] = NewOptionName;
//        }

        if (!funtypev)
           return;
        k=0;
        for (i=0;i<po_ca_show.length;i++) {
         for(j = 0; j < po_detail_value[i].length; j++){
                if(funtypev.indexOf(po_detail_value[i][j])!=-1) {
                    NewOptionName = new Option(po_detail_show[i][j], po_detail_value[i][j]);
                    form.elements[num].options[k] = NewOptionName;
                    k++;
                    }
         }
        }
}

function Do_po_Change(form){
        var num,n, i, m;
        num= GetObjID('d_position1');
        m = document.frmEdit.elements[num].selectedIndex-1;
        n = document.frmEdit.elements[num + 1].length;
        for(i = n - 1; i >= 0; i--)
                document.frmEdit.elements[num + 1].options[i] = null;

        if (m>=0) {
        for(i = 0; i < po_detail_show[m].length; i++){
                NewOptionName = new Option(po_detail_show[m][i], po_detail_value[m][i]);
                document.frmEdit.elements[num + 1].options[i] = NewOptionName;
        }
        document.frmEdit.elements[num + 1].options[0].selected = true;
        }
}

function InsertItem(ObjID, Location)
{
  len=document.frmEdit.elements[ObjID].length;
  for (counter=len; counter>Location; counter--)
  {
    Value = document.frmEdit.elements[ObjID].options[counter-1].value;
    Text2Insert  = document.frmEdit.elements[ObjID].options[counter-1].text;
    document.frmEdit.elements[ObjID].options[counter] = new Option(Text2Insert, Value);
  }
}
function GetLocation(ObjID, Value)
{
  total=document.frmEdit.elements[ObjID].length;
  for (pp=0; pp<total; pp++)
     if (document.frmEdit.elements[ObjID].options[pp].text == "---"+Value+"---")
     { return (pp);
       break;
     }
  return (-1);
}

function GetObjID(ObjName)
{
  for (var ObjID=0; ObjID < window.frmEdit.elements.length; ObjID++)
    if ( window.frmEdit.elements[ObjID].name == ObjName )
    {  return(ObjID);
       break;
    }
  return(-1);
}
function ToSubmit()
{
//  if (CheckOK)
//  {
    SelectTotal('jobarea[]');
    SelectTotal('industrytype[]');
    SelectTotal('funtype[]');
//  }
}
function SelectTotal(ObjName)
{
  ObjID = GetObjID(ObjName);
  if (ObjID != -1)
  { for (i=0; i<document.frmEdit.elements[ObjID].length; i++)
      document.frmEdit.elements[ObjID].options[i].selected = true;
  }
}
function AddItem(ObjName, DesName, CatName)
{
  //GET OBJECT ID AND DESTINATION OBJECT
  ObjID    = GetObjID(ObjName);
  DesObjID = GetObjID(DesName);
//  window.alert(document.frmEdit.elements[DesObjID].length);
  k=0;
  i = document.frmEdit.elements[ObjID].options.length;
  if (i==0)
    return;
  maxselected=0
  for (h=0; h<i; h++)
     if (document.frmEdit.elements[ObjID].options[h].selected ) {
         k=k+1;
         maxselected=h+1;
         }
  if (maxselected>=i)
     maxselected=0;
//  if ( document.frmEdit.elements[DesObjID].length + k >5 ) {
//    window.alert("最多可选择5条");
//    return;
//    }

  if (CatName != "")
    CatObjID = GetObjID(CatName);
  else
    CatObjID = 0;
  if ( ObjID != -1 && DesObjID != -1 && CatObjID != -1 )
  { jj = document.frmEdit.elements[CatObjID].selectedIndex;
    if ( CatName != "")
    { CatValue = document.frmEdit.elements[CatObjID].options[jj].text;
      CatCode  = document.frmEdit.elements[CatObjID].options[jj].value;
    }
    else
      CatValue = "";
    i = document.frmEdit.elements[ObjID].options.length;
    j = document.frmEdit.elements[DesObjID].options.length;
    for (h=0; h<i; h++)
    { if (document.frmEdit.elements[ObjID].options[h].selected )
      {  Code = document.frmEdit.elements[ObjID].options[h].value;
         Text = document.frmEdit.elements[ObjID].options[h].text;
         j = document.frmEdit.elements[DesObjID].options.length;
         if (Text.indexOf('--')!=-1) {
            for (k=j-1; k>=0; k-- ) {
              document.frmEdit.elements[DesObjID].options[k]=null;
            }
            j=0;
         }
         if (Text.substring(0,1)=='-' && Text.substring(1,2)!='-') {
            for (k=j-1; k>=0; k-- ) {
              if (((document.frmEdit.elements[DesObjID].options[k].value).substring(0,2))==(Code.substring(0,2)))
                 document.frmEdit.elements[DesObjID].options[k]=null;
            }
            j= document.frmEdit.elements[DesObjID].options.length;
         }
         HasSelected = false;
         for (k=0; k<j; k++ ) {
           if ((document.frmEdit.elements[DesObjID].options[k].text).indexOf('--')!=-1){
              HasSelected = true;
              window.alert('已经包括本选项：'+Text);
              break;
           }else if ((document.frmEdit.elements[DesObjID].options[k].text).indexOf('-')!=-1 && ((document.frmEdit.elements[DesObjID].options[k].value).substring(0,2)==Code.substring(0,2))){
              HasSelected = true;
              window.alert('已经包括本选项：'+Text);
              break;
           }
           if (document.frmEdit.elements[DesObjID].options[k].value == Code)
           {  HasSelected = true;
              break;
           }
         }
         if ( HasSelected == false)
         { if (CatValue !="")
           { Location = GetLocation(DesObjID, CatValue);
             if ( Location == -1 )
             { document.frmEdit.elements[DesObjID].options[j] =  new Option("---"+CatValue+"---",CatCode);
               document.frmEdit.elements[DesObjID].options[j+1] = new Option(Text, Code);
             }//if
             else
             { InsertItem(DesObjID, Location+1);
               document.frmEdit.elements[DesObjID].options[Location+1] = new Option(Text, Code);
             }//else
           }
           else
             document.frmEdit.elements[DesObjID].options[j] = new Option(Text, Code);
         }//if
         document.frmEdit.elements[ObjID].options[h].selected =false;
       }//if
    }//for
    document.frmEdit.elements[ObjID].options[maxselected].selected =true;
  }//if
}//end of function

function DeleteItem(ObjName)
{
  ObjID = GetObjID(ObjName);
  minselected=0;
  if ( ObjID != -1 )
  {
    for (i=window.frmEdit.elements[ObjID].length-1; i>=0; i--)
    {  if (window.frmEdit.elements[ObjID].options[i].selected)
       { // window.alert(i);
          if (minselected==0 || i<minselected)
            minselected=i;
          window.frmEdit.elements[ObjID].options[i] = null;
       }
    }
    i=window.frmEdit.elements[ObjID].length;

    if (i>0)  {
        if (minselected>=i)
           minselected=i-1;
        window.frmEdit.elements[ObjID].options[minselected].selected=true;
        }
  }
}

function CheckMultiSelect()
{
  areaID = GetObjID('jobarea[]');
  indID = GetObjID('industrytype[]');
  funID = GetObjID('funtype[]');
  i1=window.frmEdit.elements[areaID].length;
  i2=window.frmEdit.elements[indID].length;
  i3=window.frmEdit.elements[funID].length;

  if (i1==0 || i2==0 || i3==0) {
    window.alert('地点、行业、职位都是必选项(按添加按扭增加选项)');
    return false;
  }

  i=0;
  if (i1>0 && window.frmEdit.elements[areaID][0].value=='0000')
    i++;
  if (i2>0 && window.frmEdit.elements[indID][0].value=='00')
    i++;

  if (i>1) {
     window.alert('地点、行业最多只能有一个为“不限”');
     return false;
     }
  if ((window.frmEdit.age.value!=null && window.frmEdit.age.value!="") && (window.frmEdit.age.value<10 || window.frmEdit.age.value>60 || isNaN(window.frmEdit.age.value))) {
     window.alert('年龄要在10-60之间');
     return false;
  }
//  window.alert(window.frmEdit.salaryfrom.selectedIndex);
//  window.alert(window.frmEdit.salaryto.selectedIndex);
  if (window.frmEdit.salaryfrom.selectedIndex-1>window.frmEdit.salaryto.selectedIndex) {
     window.alert('请设置合理的月薪范围');
     return false;
  }

  return true;
}

function save(){
  if (!CheckMultiSelect()) return;
  ToSubmit();
  document.frmEdit.target='_top';
  document.frmEdit.action='/sc/my_se.php?save=save';
  document.frmEdit.submit();
}
function mysave(){
  if (!CheckMultiSelect()) return;
  if (!isEmail(document.frmEdit.email.value)) return;
  ToSubmit();
  document.frmEdit.target='_top';
  document.frmEdit.action='/sc/my_se.php?save=save';
  document.frmEdit.submit();
}

function search(){
  if (!CheckMultiSelect()) return;
  ToSubmit();
  document.frmEdit.target='_blank';
  document.frmEdit.action='/sc/search_result.php?begin=begin';
  document.frmEdit.submit();
}
//Added by chenquan
function mysearch(){
	if (document.frmEdit.SelectedCity.length < 2 ) {
		alert("最少要选择两个城市! ^_^  ");
		return false;
		}
	SelectTotal('SelectedCity');
//  document.frmEdit.target='_blank';
//  document.frmEdit.action='test.asp';
	document.frmEdit.submit();
	return true;
}
function presearch(){
  if (!CheckMultiSelect()) return;
  ToSubmit();
  document.frmEdit.target='_top';
  document.frmEdit.action='/sc/search_result.php?presearch=presearch';
  document.frmEdit.submit();
}

function mypresearch(){
  if (!CheckMultiSelect()) return;
  ToSubmit();
  document.frmEdit.target='_top';
  document.frmEdit.action='/sc/my_se.php?presearch=presearch';
  document.frmEdit.submit();
}
function orderpresearch(){
  if (!CheckMultiSelect()) return;
  ToSubmit();
  document.frmEdit.target='_top';
  document.frmEdit.action='/sc/my_se.php?orderpresearch=orderpresearch';
  document.frmEdit.submit();
}
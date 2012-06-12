namespace MyAddin5
{
	using System;
	using Extensibility;
	using System.Runtime.InteropServices;
      using System.Windows.Forms;
      using Microsoft.Office.Core;
      using System.Reflection;
      using System.Collections;
      using System.Collections.Generic;
      using System.Threading;

	#region Read me for Add-in installation and setup information.
	// When run, the Add-in wizard prepared the registry for the Add-in.
	// At a later time, if the Add-in becomes unavailable for reasons such as:
	//   1) You moved this project to a computer other than which is was originally created on.
	//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
	//   3) Registry corruption.
	// you will need to re-register the Add-in by building the MyAddin5Setup project, 
	// right click the project in the Solution Explorer, then choose install.
	#endregion
	
	/// <summary>
	///   The object for implementing an Add-in.
	/// </summary>
	/// <seealso class='IDTExtensibility2' />
	[GuidAttribute("862F130D-3087-4D4C-A036-492AD7AE246D"), ProgId("MyAddin5.Connect")]
	public class Connect : Object, Extensibility.IDTExtensibility2
	{
		/// <summary>
		///		Implements the constructor for the Add-in object.
		///		Place your initialization code within this method.
		/// </summary>
		public Connect()
		{
		}

		/// <summary>
		///      Implements the OnConnection method of the IDTExtensibility2 interface.
		///      Receives notification that the Add-in is being loaded.
		/// </summary>
		/// <param term='application'>
		///      Root object of the host application.
		/// </param>
		/// <param term='connectMode'>
		///      Describes how the Add-in is being loaded.
		/// </param>
		/// <param term='addInInst'>
		///      Object representing this Add-in.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnConnection(object application, Extensibility.ext_ConnectMode connectMode, object addInInst, ref System.Array custom)
		{
			
                  
                  applicationObject = application;
			addInInstance = addInInst;
                  //bool flag = applicationObject is Microsoft.Office.Interop.Visio.Application;
                  //MessageBox.Show(flag.ToString());
                  //MessageBox.Show("asd2");
                  //try
                  //{
                  //      foreach (Microsoft.Office.Interop.Visio.Document doc in (applicationObject as Microsoft.Office.Interop.Visio.Application).Documents)
                  //      {
                  //            MessageBox.Show(doc.Path);
                  //      }
                  //}
                  //catch (Exception ex)
                  //{
                  //      MessageBox.Show(ex.ToString());
                  //}
                  
                  
		}

		/// <summary>
		///     Implements the OnDisconnection method of the IDTExtensibility2 interface.
		///     Receives notification that the Add-in is being unloaded.
		/// </summary>
		/// <param term='disconnectMode'>
		///      Describes how the Add-in is being unloaded.
		/// </param>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnDisconnection(Extensibility.ext_DisconnectMode disconnectMode, ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnAddInsUpdate method of the IDTExtensibility2 interface.
		///      Receives notification that the collection of Add-ins has changed.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnAddInsUpdate(ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnStartupComplete method of the IDTExtensibility2 interface.
		///      Receives notification that the host application has completed loading.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnStartupComplete(ref System.Array custom)
		{
                  //MessageBox.Show("asd1");

                  //try
                  //{
                  //      foreach (Microsoft.Office.Interop.Visio.Document doc in (applicationObject as Microsoft.Office.Interop.Visio.Application).Documents)
                  //      {
                  //            MessageBox.Show(doc.Path + "\\"+ doc.Name);
                              
                  //      }
                  //}
                  //catch (Exception ex)
                  //{
                  //      MessageBox.Show(ex.ToString());
                  //}


                  this.ActiveWindow = (applicationObject as Microsoft.Office.Interop.Visio.Application).ActiveWindow; ;
                  AddToolBarButton();
            }

		/// <summary>
		///      Implements the OnBeginShutdown method of the IDTExtensibility2 interface.
		///      Receives notification that the host application is being unloaded.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnBeginShutdown(ref System.Array custom)
		{
		}
            CommandBarButton MyButton = null;
            CommandBarButton MyButton1 = null;
            private void AddToolBarButton()
            {
                  CommandBars oCommandBars;
                  CommandBar oStandardBar;
                  

                  try
                  {
                        oCommandBars = (CommandBars)applicationObject.GetType().InvokeMember("CommandBars", BindingFlags.GetProperty, null, applicationObject, null);

                  }
                  catch (Exception)
                  {
                        // Outlook has the CommandBars collection on the Explorer object.
                        object oActiveExplorer;
                        oActiveExplorer = applicationObject.GetType().InvokeMember("ActiveExplorer", BindingFlags.GetProperty, null, applicationObject, null);
                        oCommandBars = (CommandBars)oActiveExplorer.GetType().InvokeMember("CommandBars", BindingFlags.GetProperty, null, oActiveExplorer, null);
                  }

                  // Set up a custom button on the "Standard" commandbar.
                  try
                  {
                        oStandardBar = oCommandBars["Standard"];
                        //object omissing = System.Reflection.Missing.Value;
                        //oCommandBars[63].Controls.Add(1, omissing, omissing, omissing, omissing);

                  }
                  catch (Exception)
                  {
                        // Access names its main toolbar Database.
                        oStandardBar = oCommandBars["Database"];
                  }


                  // In case the button was not deleted, use the exiting one.
                  try
                  {
                        oStandardBar.Reset();
                        MyButton = (CommandBarButton)oStandardBar.Controls["SendToWebSevice"];
                        MyButton1 = (CommandBarButton)oStandardBar.Controls["unGroupVdx"];
                        //object tmp  =  Menu.Controls["tyu"];
                  }
                  catch (Exception)
                  {
                        object omissing = System.Reflection.Missing.Value;
                        MyButton = (CommandBarButton)oStandardBar.Controls.Add(1, omissing, omissing, omissing, omissing);
                        MyButton.Caption = "发布Vdx文件";
                        MyButton.Style = MsoButtonStyle.msoButtonCaption;

                        MyButton1 = (CommandBarButton)oStandardBar.Controls.Add(1, omissing, omissing, omissing, omissing);
                        MyButton1.Caption = "取消组合";
                        MyButton1.Style = MsoButtonStyle.msoButtonCaption;
                        //oStandardBar.Reset();
                  }

                  

                
                  //(oCommandBars["Standard"].Controls["My Custom Button"] as CommandBarButton).Click +=new _CommandBarButtonEvents_ClickEventHandler(Connect_Click);
                  // The following items are optional, but recommended. 
                  //The Tag property lets you quickly find the control 
                  //and helps MSO keep track of it when more than
                  //one application window is visible. The property is required
                  //by some Office applications and should be provided.
                  MyButton.Tag = "SendToWebSevice";

                  // The OnAction property is optional but recommended. 
                  //It should be set to the ProgID of the add-in, so that if
                  //the add-in is not loaded when a user presses the button,
                  //MSO loads the add-in automatically and then raises
                  //the Click event for the add-in to handle. 
                  MyButton.OnAction = "!<MyCOMAddin.Connect>";

                  MyButton.Visible = true;
                  MyButton.Click += new Microsoft.Office.Core._CommandBarButtonEvents_ClickEventHandler(MyButton_Click);


                  MyButton1.Tag = "unGroupVdx";
                  MyButton1.OnAction = "!<MyCOMAddin.Connect>";
                  MyButton1.Visible = true;
                  MyButton1.Click += new Microsoft.Office.Core._CommandBarButtonEvents_ClickEventHandler(MyButton1_Click);



                  object oName = applicationObject.GetType().InvokeMember("Name", BindingFlags.GetProperty, null, applicationObject, null);

                  // Display a simple message to show which application you started in.
                  //System.Windows.Forms.MessageBox.Show("This Addin is loaded by " + oName.ToString(), "MyCOMAddin");
                  oStandardBar = null;
                  oCommandBars = null;
            }

            private System.ComponentModel.BackgroundWorker SendVdxFile;
            private void MyButton_Click(CommandBarButton cmdBarbutton, ref bool cancel)
            {
                  //SendToWebSevice send = new SendToWebSevice();
                  SendVdxFile = new System.ComponentModel.BackgroundWorker();
                  SendVdxFile.DoWork += new System.ComponentModel.DoWorkEventHandler(SendVdxFile_DoWork);
                  SendVdxFile.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(SendVdxFile_RunWorkerCompleted);
                  //try
                  {
                        foreach (Microsoft.Office.Interop.Visio.Document doc in (applicationObject as Microsoft.Office.Interop.Visio.Application).Documents)
                        {
                              //doc.close();
                              frmSendWait sendWait = new frmSendWait();
                              sendWait.Show();
                              sendWait.Focus();
                              string filename = doc.Name.Replace("vsd", "vdx"); //doc.Name.Split(new char[] { '.' })[doc.Name.Split(new char[] { '.' }).Length - 1].Replace("vsd", "vdx");
                              
                              doc.SaveAs(filename);

                              SendToWebSevice send = new SendToWebSevice();
                              
                              send.SendFile(doc.Path + filename, filename, sendWait);
                              //SendVdxFile.RunWorkerAsync(SendWait);
                              break;

                        }
                  }
                  //catch (Exception ex)
                  {
                        //MessageBox.Show(ex.ToString());
                  }
                  
            }

            void SendVdxFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
            {
                  (e.Result as frmSendWait).Close();
                  (e.Result as frmSendWait).Dispose();
            }

            void SendVdxFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
            {
                  //SendToWebSevice send = new SendToWebSevice();

                  //send.SendFile(doc.Path + filename, filename);

                  //e.Result = e.Argument;
                  
            }
            Microsoft.Office.Interop.Visio.Window ActiveWindow = null;
            

            /*
            private void MyButton1_Click(CommandBarButton cmdBarbutton, ref bool cancel)
            {
                  //System.Windows.Forms.MessageBox.Show("MyButton was Clicked", "MyCOMAddin");
                  try
                  {

                        List<Microsoft.Office.Interop.Visio.Shape> tmp = new List<Microsoft.Office.Interop.Visio.Shape>();
                        //ActiveWindow.Selection.ConnectShapes();
                        //MessageBox.Show(SelectedPage.Shapes.Count.ToString());
                        //foreach (Microsoft.Office.Interop.Visio.Shape shape in SelectedPage.Shapes)
                        //{
                        //    shape.Ungroup();
                        //}
                        //MessageBox.Show(SelectedPage.Shapes.Count.ToString());
                        //foreach (Microsoft.Office.Interop.Visio.Shape shape in SelectedPage.Shapes)
                        //{
                        //    shape.Ungroup();
                        //}
                        //MessageBox.Show(SelectedPage.Shapes.Count.ToString());


                        //MessageBox.Show(ActiveWindow.Shape.Shapes.Count.ToString());

                        //ActiveWindow.SelectAll();


                        

                        int count = ActiveWindow.Shape.Shapes.Count;

                        List<Microsoft.Office.Interop.Visio.Shape> selectionList = new List<Microsoft.Office.Interop.Visio.Shape>();

                        foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                        {
                              selectionList.Add(shape);
                        }
                        //selectionList.Count.ToString()
                        for (int i = 0; i < count; i++)
                        {

                              MessageBox.Show(selectionList[i].Shapes.Count.ToString() + "UngroupShape1");
                              ActiveWindow.Select(selectionList[i], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);


                              ActiveWindow.Selection.Ungroup();
                              //if (i > 0)
                              //{
                              //    ActiveWindow.Select(selectionList[i - 1], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //}
                              MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "X3");
                              ActiveWindow.Selection.Ungroup();
                              List<Microsoft.Office.Interop.Visio.Shape> UngroupShape = new List<Microsoft.Office.Interop.Visio.Shape>();

                              MessageBox.Show(selectionList[i].Shapes.Count.ToString() + "UngroupShape");
                              for (int j = 0; j < tmp.Count; j++)
                              {
                                    ActiveWindow.Select(tmp[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                    MessageBox.Show("XXX");
                              }

                              foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                              {
                                    UngroupShape.Add(shape);
                              }
                              
                              
                              //if (i > 0)
                              //{
                                    
                                    
                              //      Microsoft.Office.Interop.Visio.Shape Shapetmp = ActiveWindow.Selection.ContainingShape;
                              //      ActiveWindow.Selection.DeselectAll();
                              //      // MessageBox.Show(Shapetmp.Shapes.Count.ToString() +"T");

                              //      foreach (Microsoft.Office.Interop.Visio.Shape Shape in Shapetmp.Shapes)
                              //      {
                              //            ActiveWindow.Select(Shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                              //      }

                              //      //if (i > 0)
                              //      //{
                              //      //    ActiveWindow.Select(selectionList[i - 1], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //      //}
                              //      MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "X1");
                              //}
                              //else
                              //{

                              //      foreach (Microsoft.Office.Interop.Visio.Shape Shape in ActiveWindow.Selection.ContainingShape.Shapes)
                              //      {
                              //            ActiveWindow.Select(Shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                              //      }
                              //}
                              //for (int j = 0; j < count; j++)
                              //{
                              //      if (i != j)
                              //      {
                              //            ActiveWindow.Select(selectionList[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //      }
                              //}
                              //// MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString());
                              //if (i > 0)
                              //{
                              //      MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "s");
                              //      ActiveWindow.Select(selectionList[i - 1], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselectAll);
                              //      MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "s1");
                              //      //if (shape.Shapes.Count >=172)
                              //      //{
                              //      //    MessageBox.Show("continue1");
                              //      //    continue;
                              //      //}
                              //}
                              //MessageBox.Show(",");
                              bool Ungroup = true;
                              while (true)
                              {
                                    Ungroup = true;
                                    // MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString()+",");
                                    for (int j = 0; j < UngroupShape.Count;j++)
                                    {

                                          if (UngroupShape[j].Shapes.Count > 1)
                                          {
                                                foreach(Microsoft.Office.Interop.Visio.Shape shape in UngroupShape[j].Shapes)
                                                {
                                                      UngroupShape.Add(shape);
                                                }

                                                UngroupShape[j].Ungroup();
                                                UngroupShape.RemoveAt(j);
                                                Ungroup = false;
                                                break;
                                          }
                                          //for (int j = 0; j < count; j++)
                                          //{
                                          //    if (i != j)
                                          //    {
                                          //        ActiveWindow.Select(selectionList[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                          //    }
                                          //}
                                          //if (i>0)
                                          //{
                                          //    ActiveWindow.Select(selectionList[i-1], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);

                                          //    //if (shape.Shapes.Count >=172)
                                          //    //{
                                          //    //    MessageBox.Show("continue1");
                                          //    //    continue;
                                          //    //}
                                          //}
                                          //if (shape.Shapes.Count > 1)
                                          //{

                                          //      MessageBox.Show(shape.Shapes.Count.ToString() + "k1");
                                          //      MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString() + "k");

                                          //      ActiveWindow.Selection.Ungroup();
                                          //      //MessageBox.Show("sub");
                                          //      Ungroup = false;
                                          //      break;
                                          //}
                                    }
                                    if (Ungroup)
                                    {
                                          //foreach (Microsoft.Office.Interop.Visio.Shape Shape in ActiveWindow.Selection.ContainingShape.Shapes)
                                          //{
                                          //    for (int j = 0; j < count; j++)
                                          //    {
                                          //        if (selectionList[j] != Shape)
                                          //        {
                                          //            ActiveWindow.Select(Shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                                          //            break;
                                          //        }
                                          //        else
                                          //        {
                                          //            MessageBox.Show(";");
                                          //            ActiveWindow.Select(Shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                          //        }
                                          //    }

                                          //}
                                          break;
                                    }
                              }
                              MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString());

                              //for (int j = 0; j < count; j++)
                              //{
                              //      if (i != j)
                              //      {
                              //            ActiveWindow.Select(selectionList[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //      }
                              //      else
                              //      {
                              //            //ActiveWindow.Select(selectionList[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                              //      }
                              //}
                              //MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString());
                              //if (i > 0)
                              //{
                              //    ActiveWindow.Select(selectionList[i - 1], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);


                              //}
                              //ActiveWindow.DeselectAll();
                              ActiveWindow.DeselectAll();
                              //for (int j = 0; j < count; j++)
                              //{
                              //      if (i != j)
                              //      {
                              //            ActiveWindow.Select(selectionList[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                         
                              //      }
                              //}
                              for (int j = 0; j < UngroupShape.Count; j++)
                              {
                                    ActiveWindow.Select(UngroupShape[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSelect);
                              }
                              MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "sos");
                              ActiveWindow.Selection.Group();
                              //MessageBox.Show(ActiveWindow.Selection.Count.ToString()+".");
                              selectionList[i] = ActiveWindow.Selection.ContainingShape;

                              tmp.Add(ActiveWindow.Selection.ContainingShape);
                              //foreach (Microsoft.Office.Interop.Visio.Shape selectedShape in ActiveWindow.Selection.ContainingShape.Shapes)
                              //{
                              //    ActiveWindow.Select(selectedShape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //}
                              // MessageBox.Show(".");
                              ActiveWindow.DeselectAll();

                        }
                        //ActiveWindow.Shape.SelectionAdded+=new Microsoft.Office.Interop.Visio.EShape_SelectionAddedEventHandler(Shape_SelectionAdded);
                        //ActiveWindow.Shape.Ungroup();
                        //ActiveWindow.Shape.Ungroup();
                        //ActiveWindow.Shape.Group();
                        //ActiveWindow.Selection.Ungroup();
                        //ActiveWindow.Selection.Ungroup();

                        //ActiveWindow.Selection.Group();

                        // ActiveWindow.Selection.ContainingShape.Ungroup();
                        // //ActiveWindow.Selection.ConnectShapes();
                        // ActiveWindow.Selection.ContainingShape.Ungroup();
                        ////ActiveWindow.Selection.ConnectShapes();
                        // ActiveWindow.Selection.ContainingShape.Group();

                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.ToString());
                  }
            }

            */

            /*
            private void MyButton1_Click(CommandBarButton cmdBarbutton, ref bool cancel)
            {
                  //System.Windows.Forms.MessageBox.Show("MyButton was Clicked", "MyCOMAddin");
                  try
                  {
                        List<Microsoft.Office.Interop.Visio.Shape> selectionList = new List<Microsoft.Office.Interop.Visio.Shape>();

                        foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                        {
                              selectionList.Add(shape);
                        }

                        

                        List<Microsoft.Office.Interop.Visio.Shape> UngroupShape = new List<Microsoft.Office.Interop.Visio.Shape>();



                        ActiveWindow.Selection.Ungroup();

                        ActiveWindow.Selection.Ungroup();

                        foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                        {
                              if (selectionList.Contains(shape))
                              {
                                    //MessageBox.Show("asd");
                                    continue;
                              }

                              UngroupShape.Add(shape);
                              
                        }
                        bool Ungroup = true;
                        while (true)
                        {
                              Ungroup = true;
                              // MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString()+",");
                              for (int j = 0; j < UngroupShape.Count; j++)
                              {

                                    if (UngroupShape[j].Shapes.Count > 1)
                                    {
                                          foreach (Microsoft.Office.Interop.Visio.Shape shape in UngroupShape[j].Shapes)
                                          {
                                                UngroupShape.Add(shape);
                                          }

                                          UngroupShape[j].Ungroup();
                                          UngroupShape.RemoveAt(j);
                                          Ungroup = false;
                                          break;
                                    }

                              }
                              if (Ungroup)
                              {

                                    break;
                              }
                        }
                        for (int j = 0; j < UngroupShape.Count; j++)
                        {
                              ActiveWindow.Select(UngroupShape[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSelect);
                        }
                        MessageBox.Show(ActiveWindow.Selection.Count.ToString());
                        ActiveWindow.SelectAll();
                        for (int i = 0; i < selectionList.Count; i++)
                        {
                              ActiveWindow.Select(selectionList[i], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                        }
                        ActiveWindow.Selection.Group();





                        //ActiveWindow.DeselectAll();
                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.ToString());
                  }
            }

            */
            /*
            private void MyButton1_Click(CommandBarButton cmdBarbutton, ref bool cancel)
            {
                  //System.Windows.Forms.MessageBox.Show("MyButton was Clicked", "MyCOMAddin");



                  try
                  {
                        List<Microsoft.Office.Interop.Visio.Shape> selectionList1 = new List<Microsoft.Office.Interop.Visio.Shape>();
                        foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                        {
                              selectionList1.Add(shape);


                              //// Microsoft.Office.Interop.Visio.Cell shapeCell = shape.get_CellsSRC(
                              ////(short)Microsoft.Office.Interop.Visio.
                              //// VisSectionIndices.visSectionFirstComponent, 0,2);

                              //// MessageBox.Show(shapeCell.get_ResultStr((short)Microsoft.Office.Interop.Visio.VisSectionIndices.visSectionFirstComponent+2));

                        }

                        int count = selectionList1.Count;
                        for (int k = 0; k < count; k++)
                        {
                              List<Microsoft.Office.Interop.Visio.Shape> selectionList = new List<Microsoft.Office.Interop.Visio.Shape>();

                              foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                              {
                                    selectionList.Add(shape);
                              }



                              List<Microsoft.Office.Interop.Visio.Shape> UngroupShape = new List<Microsoft.Office.Interop.Visio.Shape>();

                              ActiveWindow.Select(selectionList1[k], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);

                              ActiveWindow.Selection.Ungroup();

                              Thread.Sleep(1000);

                              ActiveWindow.Selection.Ungroup();

                              Thread.Sleep(1000);


                              foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                              {
                                    if (selectionList.Contains(shape))
                                    {

                                          ActiveWindow.Select(shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                          continue;
                                    }

                                    UngroupShape.Add(shape);


                              }
                              bool Ungroup = true;
                              while (true)
                              {
                                    Ungroup = true;
                                    // MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString()+",");
                                    for (int j = 0; j < UngroupShape.Count; j++)
                                    {

                                          if (UngroupShape[j].Shapes.Count > 1)
                                          {
                                                foreach (Microsoft.Office.Interop.Visio.Shape shape in UngroupShape[j].Shapes)
                                                {
                                                      UngroupShape.Add(shape);
                                                }

                                                UngroupShape[j].Ungroup();
                                                UngroupShape.RemoveAt(j);
                                                j = j - 1;
                                                Ungroup = false;
                                                //break;
                                          }

                                    }
                                    if (Ungroup)
                                    {

                                          break;
                                    }
                              }
                              for (int j = 0; j < UngroupShape.Count; j++)
                              {
                                    ActiveWindow.Select(UngroupShape[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSelect);
                              }
                              //MessageBox.Show(ActiveWindow.Selection.Count.ToString());
                              ActiveWindow.SelectAll();
                              for (int i = 0; i < selectionList.Count; i++)
                              {
                                    ActiveWindow.Select(selectionList[i], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              }
                              ActiveWindow.Selection.Group();

                              ActiveWindow.DeselectAll();
                        }

                        MessageBox.Show("重组完成");

                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.ToString());
                  }
            }
            */

            private void MyButton1_Click(CommandBarButton cmdBarbutton, ref bool cancel)
            {
                  //System.Windows.Forms.MessageBox.Show("MyButton was Clicked", "MyCOMAddin");



                  try
                  {
                        
                        List<Microsoft.Office.Interop.Visio.Shape> selectionList1 = new List<Microsoft.Office.Interop.Visio.Shape>();
                        //foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                        //{
                        //      selectionList1.Add(shape);
                        //}
                        ActiveWindow.SelectAll();
                        foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                        {
                              selectionList1.Add(shape);
                        }
                        //MessageBox.Show(selectionList1.Count.ToString());
                        ActiveWindow.DeselectAll();
                        int count = selectionList1.Count;
                        MessageBox.Show(count.ToString());
                        for (int k = 0; k < count; k++)
                        {
                              List<Microsoft.Office.Interop.Visio.Shape> selectionList = new List<Microsoft.Office.Interop.Visio.Shape>();

                              //foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Shape.Shapes)
                              //{
                              //      selectionList.Add(shape);
                              //}



                              List<Microsoft.Office.Interop.Visio.Shape> UngroupShape = new List<Microsoft.Office.Interop.Visio.Shape>();

                              ActiveWindow.Select(selectionList1[k], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                              //MessageBox.Show("stop");
                              //ActiveWindow.Selection.Ungroup();

                              //Thread.Sleep(1000);

                              //ActiveWindow.Selection.Ungroup();

                              //Thread.Sleep(1000);/


                              //foreach (Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                              //{
                              //      if (selectionList.Contains(shape))
                              //      {

                              //            ActiveWindow.Select(shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                              //            MessageBox.Show("No");
                              //            continue;

                              //      }

                              //      UngroupShape.Add(shape);
                              //      MessageBox.Show("Add");

                              //}

                              //MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "S");
                              //ActiveWindow.Selection.Ungroup();
                              //Thread.Sleep(500);
                              bool operateFlag = false;
                              foreach(Microsoft.Office.Interop.Visio.Shape shape in ActiveWindow.Selection.ContainingShape.Shapes)
                              {
                                    if (selectionList1[k] == shape)
                                    {
                                          //MessageBox.Show(shape.Shapes.Count.ToString() + "X1");
                                          //MessageBox.Show(shape.ContainingShape.Shapes.Count.ToString() + "X2");
                                          if (shape.Shapes.Count == 0)
                                          {
                                                UngroupShape.Add(shape);
                                                
                                                operateFlag = true;
                                                break;
                                          }
                                          foreach (Microsoft.Office.Interop.Visio.Shape shape1 in shape.Shapes)
                                          {
                                                
                                                UngroupShape.Add(shape1);
                                          }
                                          ActiveWindow.DeselectAll();
                                          ActiveWindow.Select(shape, (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSubSelect);
                                          break;
                                    }
                              }
                              //MessageBox.Show(ActiveWindow.Selection.Count.ToString() + "X");
                              
                              
                              Thread.Sleep(100);
                              if (!operateFlag)
                              {
                                    ActiveWindow.Selection.Ungroup();


                                   // Thread.Sleep(500);

                                    bool Ungroup = true;
                                    while (true)
                                    {
                                          Ungroup = true;
                                          // MessageBox.Show(ActiveWindow.Selection.ContainingShape.Shapes.Count.ToString()+",");

                                          for (int j = 0; j < UngroupShape.Count; j++)
                                          {

                                                if (UngroupShape[j].Shapes.Count > 1)
                                                {
                                                      foreach (Microsoft.Office.Interop.Visio.Shape shape in UngroupShape[j].Shapes)
                                                      {
                                                            UngroupShape.Add(shape);
                                                      }

                                                      UngroupShape[j].Ungroup();
                                                      UngroupShape.RemoveAt(j);
                                                      j = j - 1;
                                                      Ungroup = false;
                                                      //break;
                                                }

                                          }
                                          if (Ungroup)
                                          {

                                                break;
                                          }
                                    }
                                    ActiveWindow.DeselectAll();


                                    for (int j = 0; j < UngroupShape.Count; j++)
                                    {
                                          ActiveWindow.Select(UngroupShape[j], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visSelect);
                                    }
                                    //MessageBox.Show(ActiveWindow.Selection.Count.ToString());
                                    //ActiveWindow.SelectAll();
                                    //for (int i = 0; i < selectionList.Count; i++)
                                    //{
                                    //      ActiveWindow.Select(selectionList[i], (short)Microsoft.Office.Interop.Visio.VisSelectArgs.visDeselect);
                                    //}
                                    //MessageBox.Show(ActiveWindow.Selection.Count.ToString());
                                    //MessageBox.Show("adsf");
                                    ActiveWindow.Selection.Group();
                              }
                              ActiveWindow.DeselectAll();
                        }

                        MessageBox.Show("重组完成");

                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.ToString());
                  }
            }

		private object applicationObject;
		private object addInInstance;
	}
}
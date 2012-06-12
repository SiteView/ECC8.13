package Fusion.Api;

import java.awt.Point;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:35
 */
public class ShapeControlDef extends ControlDef {

	public ShapeControlDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ShapeControlDef(Object fusionObject){

	}

	/**
	 * 
	 * @param point
	 */
	public int AddPoint(Point point){
		return 0;
	}

	public int ArcHeight(){
		return 0;
	}

	public int ArcWidth(){
		return 0;
	}

	public String AssociatedFieldName(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public System.Drawing.Drawing2D.DashStyle DashStyle(){
		return null;
	}

	public LineCap EndCap(){
		return null;
	}

	public boolean IsArc(){
		return null;
	}

	public boolean IsClosed(){
		return null;
	}

	public boolean IsEllipse(){
		return null;
	}

	public boolean IsFilled(){
		return null;
	}

	public boolean IsLines(){
		return null;
	}

	public int LineWidth(){
		return 0;
	}

	public List Points(){
		return null;
	}

	public void RemoveAllPoints(){

	}

	/**
	 * 
	 * @param point
	 */
	public void RemovePoint(Point point){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public void RemovePointAt(int nIndex){

	}

	public int StartAngle(){
		return 0;
	}

	public LineCap StartCap(){
		return null;
	}

	public int SweepAngle(){
		return 0;
	}

	private Fusion.Presentation.ShapeControlDef WhoAmI(){
		return null;
	}

}
package Fusion.HoursOfOperation.Model;

import Fusion.control.CollectionChangeEventArgs;
import Fusion.control.DataColumn;
import Fusion.control.DataRow;
import Fusion.control.DataRowAction;
import Fusion.control.DataRowBuilder;
import Fusion.control.DataRowChangeEventArgs;
import Fusion.control.DataSet;
import Fusion.control.DataTable;
import Fusion.control.DateTime;
import Fusion.control.EventArgs;
import Fusion.control.IEnumerable;
import Fusion.control.IEnumerator;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.Type;
import Fusion.control.XmlReader;
import Fusion.control.XmlSchema;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:23
 */
public class HOPData extends DataSet {

	public class HOPRowChangeEventHandler {

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:23
	 */
	public class HOPDataTable extends DataTable implements IEnumerable {

		private DataColumn columnEndsAfter;
		private DataColumn columnSchedule;
		private DataColumn columnStartDate;
		private DataColumn columnTaskIdx;
		private DataColumn columnTaskName;



		public void finalize() throws Throwable {
			super.finalize();
		}

		public HOPDataTable(){

		}

		/**
		 * 
		 * @param table
		 */
		public HOPDataTable(DataTable table){

		}

		/**
		 * 
		 * @param row
		 */
		public void AddHOPRow(HOPData.HOPRow row){

		}

		/**
		 * 
		 * @param TaskIdx
		 * @param TaskName
		 * @param Schedule
		 * @param StartDate
		 * @param EndsAfter
		 */
		public HOPData.HOPRow AddHOPRow(long TaskIdx, String TaskName, String Schedule, DateTime StartDate, String EndsAfter){
			return null;
		}

		public DataTable Clone(){
			return null;
		}

		public int Count(){
			return 0;
		}

		protected DataTable CreateInstance(){
			return null;
		}

		public DataColumn EndsAfterColumn(){
			return null;
		}

		public IEnumerator GetEnumerator(){
			return null;
		}

		protected Type GetRowType(){
			return null;
		}

		public HOPData.HOPRowChangeEventHandler HOPRowChanged(){
			return null;
		}

		public HOPData.HOPRowChangeEventHandler HOPRowChanging(){
			return null;
		}

		public HOPData.HOPRowChangeEventHandler HOPRowDeleted(){
			return null;
		}

		public HOPData.HOPRowChangeEventHandler HOPRowDeleting(){
			return null;
		}

		private void InitClass(){

		}

		public void InitVars(){

		}

		public HOPData.HOPRow NewHOPRow(){
			return null;
		}

		/**
		 * 
		 * @param builder
		 */
		protected DataRow NewRowFromBuilder(DataRowBuilder builder){
			return null;
		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowChanged(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowChanging(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowDeleted(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param e
		 */
		protected void OnRowDeleting(DataRowChangeEventArgs e){

		}

		/**
		 * 
		 * @param row
		 */
		public void RemoveHOPRow(HOPData.HOPRow row){

		}

		public DataColumn ScheduleColumn(){
			return null;
		}

		public DataColumn StartDateColumn(){
			return null;
		}

		public DataColumn TaskIdxColumn(){
			return null;
		}

		public DataColumn TaskNameColumn(){
			return null;
		}

		/**
		 * 
		 * @param index
		 */
		public HOPData.HOPRow getThis(int index){
			return null;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:23
	 */
	public class HOPRow extends DataRow {

		private HOPData.HOPDataTable tableHOP;

		public HOPRow(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param rb
		 */
		public HOPRow(DataRowBuilder rb){

		}

		public String EndsAfter(){
			return "";
		}

		public Boolean IsEndsAfterNull(){
			return null;
		}

		public Boolean IsScheduleNull(){
			return null;
		}

		public Boolean IsStartDateNull(){
			return null;
		}

		public Boolean IsTaskIdxNull(){
			return null;
		}

		public Boolean IsTaskNameNull(){
			return null;
		}

		public String Schedule(){
			return "";
		}

		public void SetEndsAfterNull(){

		}

		public void SetScheduleNull(){

		}

		public void SetStartDateNull(){

		}

		public void SetTaskIdxNull(){

		}

		public void SetTaskNameNull(){

		}

		public DateTime StartDate(){
			return null;
		}

		public long TaskIdx(){
			return 0;
		}

		public String TaskName(){
			return "";
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:23
	 */
	public class HOPRowChangeEvent extends EventArgs {

		private DataRowAction eventAction;
		private HOPData.HOPRow eventRow;

		public HOPRowChangeEvent(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param row
		 * @param action
		 */
		public HOPRowChangeEvent(HOPData.HOPRow row, DataRowAction action){

		}

		public DataRowAction Action(){
			return null;
		}

		public HOPData.HOPRow Row(){
			return null;
		}

	}

	private HOPDataTable tableHOP;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public HOPData(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected HOPData(SerializationInfo info, StreamingContext context){

	}

	public DataSet Clone(){
		return null;
	}

	protected XmlSchema GetSchemaSerializable(){
		return null;
	}

	public HOPDataTable HOP(){
		return null;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public void HOPRowChangeEventHandler(Object sender, HOPData.HOPRowChangeEvent e){

	}

	private void InitClass(){

	}

	public void InitVars(){

	}

	/**
	 * 
	 * @param reader
	 */
	protected void ReadXmlSerializable(XmlReader reader){

	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void SchemaChanged(Object sender, CollectionChangeEventArgs e){

	}

	private Boolean ShouldSerializeHOP(){
		return null;
	}

	protected Boolean ShouldSerializeRelations(){
		return null;
	}

	protected Boolean ShouldSerializeTables(){
		return null;
	}

}
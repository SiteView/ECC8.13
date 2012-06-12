package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:43
 */
public class QueryResultInfo implements IQueryResultInfo {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:43
	 */
	private class Tags {

		private String OrderByList = "OrderByList";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getOrderByList(){
			return OrderByList;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setOrderByList(String newVal){
			OrderByList = newVal;
		}

	}

	private ArrayList m_alOrderByFields;
	private boolean m_bAdditionalRows;
	private boolean m_bResultLinkedBasedRel;
	private DataSetResult m_DataSetResult;
	private int m_nFound;
	private int m_nReturned;
	private Fusion.PagingInfo m_pagingInfo;
	private String m_strBusObName;
	private String m_strBusObNameColumn;
	private String m_strRecIdColumn;
	private QueryInfoToGet m_typeDataHeld;



	public void finalize() throws Throwable {

	}

	public QueryResultInfo(){

	}

	/**
	 * 
	 * @param colOrderByFields
	 * @param strBusObName
	 * @param strRecIdColumn
	 * @param strBusObNameColumn
	 * @param typeDataHeld
	 * @param bLinkedBased
	 */
	public QueryResultInfo(List colOrderByFields, String strBusObName, String strRecIdColumn, String strBusObNameColumn, QueryInfoToGet typeDataHeld, boolean bLinkedBased){

	}

	public boolean AdditionalRows(){
		return null;
	}

	public String BusinessObjectName(){
		return "";
	}

	public String BusObNameColumn(){
		return "";
	}

	public int Found(){
		return 0;
	}

	public List OrderByList(){
		return null;
	}

	public Fusion.PagingInfo PagingInfo(){
		return null;
	}

	public String RecIdColumn(){
		return "";
	}

	public DataSetResult Result(){
		return null;
	}

	public boolean ResultFromLinkBasedRelationship(){
		return null;
	}

	public int Returned(){
		return 0;
	}

	public String RowPositionXml(){
		return "";
	}

	/**
	 * 
	 * @param nCount
	 */
	public void SetCountRetrieved(int nCount){

	}

	/**
	 * 
	 * @param nTableItems
	 */
	public void SetEntireTableRetrieved(int nTableItems){

	}

	/**
	 * 
	 * @param nPos
	 * @param oStartValue
	 * @param oEndValue
	 */
	public void SetLastOrderByValues(int nPos, Object oStartValue, Object oEndValue){

	}

	/**
	 * 
	 * @param nPos
	 * @param oStartValue
	 * @param oEndValue
	 * @param bAscending
	 */
	public void SetLastOrderByValues(int nPos, Object oStartValue, Object oEndValue, boolean bAscending){

	}

	public void SetNoDataFound(){

	}

	/**
	 * 
	 * @param nFound
	 * @param nRetrieved
	 */
	public void SetPartialDataRetrieved(int nFound, int nRetrieved){

	}

	public QueryInfoToGet TypeOfDataHeld(){
		return null;
	}

}
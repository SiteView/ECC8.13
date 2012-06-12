package Fusion;

import java.util.ArrayList;

import Fusion.control.ICollection;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:30
 */
public class MessageInfoList {

	private ArrayList m_listMessages;
	private int m_nTotalErrors;
	private int m_nTotalMessages;
	private int m_nTotalWarnings;



	public void finalize() throws Throwable {

	}

	public MessageInfoList(){

	}

	/**
	 * 
	 * @param msgList
	 */
	public MessageInfoList(MessageInfoList msgList){

	}

	/**
	 * 
	 * @param msgInfo
	 */
	public int Add(MessageInfo msgInfo){
		return 0;
	}

	/**
	 * 
	 * @param msgList
	 */
	public void Add(MessageInfoList msgList){

	}

	/**
	 * 
	 * @param icoll
	 */
	public void Add(ICollection icoll){

	}

	/**
	 * 
	 * @param cat
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 */
	public MessageInfo Add(MessageCategory cat, String strResourceId, String strSource, String strAltMessage){
		return null;
	}

	/**
	 * 
	 * @param strMessage
	 * @param strSource
	 * @param severity
	 */
	public ErrorInfo AddError(String strMessage, String strSource, ErrorSeverity severity){
		return null;
	}

	/**
	 * 
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 * @param severity
	 */
	public ErrorInfo AddError(String strResourceId, String strSource, String strAltMessage, ErrorSeverity severity){
		return null;
	}

	/**
	 * 
	 * @param strMessage
	 * @param strSource
	 */
	public ErrorInfo AddWarning(String strMessage, String strSource){
		return null;
	}

	/**
	 * 
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 * @param severity
	 */
	public ErrorInfo AddWarning(String strResourceId, String strSource, String strAltMessage, ErrorSeverity severity){
		return null;
	}

	public ICollection AllMessages(){
		return null;
	}

	public void Clear(){

	}

	/**
	 * 
	 * @param msgInfo
	 */
	public Boolean Contains(MessageInfo msgInfo){
		return null;
	}

	public int Count(){
		return 0;
	}

	/**
	 * 
	 * @param bWarning
	 * @param strResourceId
	 * @param strSource
	 * @param strMessage
	 * @param severity
	 */
	public ErrorInfo CreateErrorInfo(Boolean bWarning, String strResourceId, String strSource, String strMessage, ErrorSeverity severity){
		return null;
	}

	/**
	 * 
	 * @param cat
	 * @param strResourceId
	 * @param strSource
	 * @param strMessage
	 */
	public MessageInfo CreateMessageInfo(MessageCategory cat, String strResourceId, String strSource, String strMessage){
		return null;
	}

	public ICollection Errors(){
		return null;
	}

	public ICollection ErrorsAndWarnings(){
		return null;
	}

	public String GetErrorsAsString(){
		return "";
	}

	/**
	 * 
	 * @param cat
	 */
	private ArrayList GetMessages(MessageCategory cat){
		return null;
	}

	/**
	 * 
	 * @param category
	 */
	public String GetMessagesAsString(MessageCategory category){
		return "";
	}

	/**
	 * 
	 * @param category
	 * @param bRemoveDoubles
	 */
	public String GetMessagesAsString(MessageCategory category, Boolean bRemoveDoubles){
		return "";
	}

	public String GetWarningsAsString(){
		return "";
	}

	public Boolean HasErrors(){
		return null;
	}

	public Boolean HasErrorsOrWarnings(){
		return null;
	}

	public Boolean HasMessages(){
		return null;
	}

	public Boolean HasWarnings(){
		return null;
	}

	/**
	 * 
	 * @param msgInfo
	 */
	public int IndexOf(MessageInfo msgInfo){
		return 0;
	}

	/**
	 * 
	 * @param msgInfo
	 * @param startIndex
	 */
	public int IndexOf(MessageInfo msgInfo, int startIndex){
		return 0;
	}

	/**
	 * 
	 * @param msgInfo
	 * @param startIndex
	 * @param count
	 */
	public int IndexOf(MessageInfo msgInfo, int startIndex, int count){
		return 0;
	}

	/**
	 * 
	 * @param index
	 * @param msgInfo
	 */
	public void Insert(int index, MessageInfo msgInfo){

	}

	/**
	 * 
	 * @param index
	 * @param cat
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 */
	public MessageInfo Insert(int index, MessageCategory cat, String strResourceId, String strSource, String strAltMessage){
		return null;
	}

	/**
	 * 
	 * @param index
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 * @param severity
	 */
	public ErrorInfo InsertError(int index, String strResourceId, String strSource, String strAltMessage, ErrorSeverity severity){
		return null;
	}

	/**
	 * 
	 * @param index
	 * @param strResourceId
	 * @param strSource
	 * @param strAltMessage
	 * @param severity
	 */
	public ErrorInfo InsertWarning(int index, String strResourceId, String strSource, String strAltMessage, ErrorSeverity severity){
		return null;
	}

	public ICollection Messages(){
		return null;
	}

	/**
	 * 
	 * @param msgInfo
	 */
	public void Remove(MessageInfo msgInfo){

	}

	/**
	 * 
	 * @param index
	 */
	public void RemoveAt(int index){

	}

	/**
	 * 
	 * @param index
	 */
	public MessageInfo getThis(int index){
		return null;
	}

	public int TotalErrors(){
		return 0;
	}

	public int TotalMessages(){
		return 0;
	}

	public int TotalWarnings(){
		return 0;
	}

	/**
	 * 
	 * @param msgInfo
	 * @param nInc
	 */
	private void UpdateCount(MessageInfo msgInfo, int nInc){

	}

	public ICollection Warnings(){
		return null;
	}

}
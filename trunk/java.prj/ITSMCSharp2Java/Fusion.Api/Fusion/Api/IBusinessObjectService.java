package Fusion.Api;

import java.util.ArrayList;

import javax.xml.bind.annotation.XmlSchema;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:48
 */
public interface IBusinessObjectService {

	/**
	 * 
	 * @param businessObjects
	 * @param groupName
	 */
	public void AddObjectsToGroup(BusinessObjectCollection businessObjects, String groupName);

	/**
	 * 
	 * @param recID
	 * @param businessObjectName
	 * @param groupName
	 */
	public void AddObjectToGroup(String recID, String businessObjectName, String groupName);

	/**
	 * 
	 * @param bo
	 */
	public XmlDocument BO2XML(BusinessObject bo);

	/**
	 * 
	 * @param bos
	 */
	public XmlDocument BO2XML(List bos);

	/**
	 * 
	 * @param bo
	 * @param bIncludeEmptyFields
	 */
	public XmlDocument BO2XML(BusinessObject bo, boolean bIncludeEmptyFields);

	/**
	 * 
	 * @param bos
	 * @param bIncludeEmptyFields
	 */
	public XmlDocument BO2XML(List bos, boolean bIncludeEmptyFields);

	/**
	 * 
	 * @param bo
	 */
	public String BO2XMLString(BusinessObject bo);

	/**
	 * 
	 * @param bos
	 */
	public String BO2XMLString(List bos);

	/**
	 * 
	 * @param bo
	 * @param bIncludeEmptyFields
	 */
	public String BO2XMLString(BusinessObject bo, boolean bIncludeEmptyFields);

	/**
	 * 
	 * @param bos
	 * @param bIncludeEmptyFields
	 */
	public String BO2XMLString(List bos, boolean bIncludeEmptyFields);

	/**
	 * 
	 * @param strDefObjectName
	 */
	public BusinessObject Create(String strDefObjectName);

	/**
	 * 
	 * @param strDefObjectName
	 * @param init
	 */
	public BusinessObject Create(String strDefObjectName, boolean init);

	/**
	 * 
	 * @param strId
	 * @param strName
	 */
	public IBusObKey CreateBusObKey(String strId, String strName);

	public IBusObKeyList CreateEmptyKeyList();

	public IVirtualBusObKeyList CreateEmptyVirtualKeyList();

	/**
	 * 
	 * @param data
	 * @param recIdName
	 */
	public IVirtualBusObKeyList CreateVirtualKeyListByDataTable(DataTable data, String recIdName);

	/**
	 * 
	 * @param defBusOb
	 * @param strBusObId
	 */
	public void DeleteBusinessObject(BusinessObjectDef defBusOb, String strBusObId);

	/**
	 * 
	 * @param strBusObName
	 * @param strBusObId
	 */
	public void DeleteBusinessObject(String strBusObName, String strBusObId);

	public void ExpireCache();

	/**
	 * 
	 * @param BusObName
	 */
	public void ExpireSpecificCache(String BusObName);

	/**
	 * 
	 * @param sObName
	 */
	public XmlSchema GetBOSchema(String sObName);

	/**
	 * 
	 * @param sObName
	 */
	public String GetBOSchemaString(String sObName);

	/**
	 * 
	 * @param query
	 */
	public BusinessObject GetBusinessObject(FusionQuery query);

	/**
	 * 
	 * @param busObKey
	 */
	public BusinessObject GetBusinessObject(IBusObKey busObKey);

	/**
	 * 
	 * @param busObKey
	 */
	public BusinessObject GetBusinessObject(IVirtualBusObKey busObKey);

	/**
	 * 
	 * @param Name
	 * @param Id
	 */
	public BusinessObject GetBusinessObject(String Name, String Id);

	/**
	 * 
	 * @param strName
	 * @param strRecIdFieldName
	 * @param strId
	 */
	public BusinessObject GetBusinessObject(String strName, String strRecIdFieldName, String strId);

	/**
	 * 
	 * @param keyList
	 */
	public BusinessObject GetCurrentBusinessObject(IBusObKeyList keyList);

	/**
	 * 
	 * @param keyList
	 */
	public BusinessObject GetCurrentBusinessObject(IVirtualKeyList keyList);

	/**
	 * 
	 * @param defHOP
	 * @param StartDateTime
	 * @param EndDateTime
	 */
	public double GetDuration(HoursOfOperationDef defHOP, Date StartDateTime, Date EndDateTime);

	/**
	 * 
	 * @param HopID
	 * @param StartDateTime
	 * @param EndDateTime
	 */
	public double GetDuration(String HopID, Date StartDateTime, Date EndDateTime);

	/**
	 * 
	 * @param RecID
	 * @param LookupDate
	 * @param LookupParameter
	 */
	public String GetParameterValueByEmployee(String RecID, Date LookupDate, String LookupParameter);

	/**
	 * 
	 * @param busObKey
	 * @param relationships
	 */
	public BusinessObject GetParentBusinessObject(IBusObKey busObKey, QueryRelationshipInfo[] relationships);

	/**
	 * 
	 * @param sName
	 */
	public XmlSchema GetQuerySchema(String sName);

	/**
	 * 
	 * @param sName
	 */
	public String GetQuerySchemaString(String sName);

	/**
	 * 
	 * @param sName
	 */
	public XmlSchema GetQuickActionSchema(String sName);

	/**
	 * 
	 * @param sName
	 */
	public String GetQuickActionSchemaString(String sName);

	/**
	 * 
	 * @param HopID
	 * @param CreateDateTime
	 * @param OffSet
	 */
	public Date GetTargetDateTime(String HopID, Date CreateDateTime, int OffSet);

	public Fusion.Api.PagedQueryResolver PagedQueryResolver();

	/**
	 * 
	 * @param strBusObName
	 * @param rows
	 */
	public List SerializeFromDataRows(String strBusObName, DataRowCollection rows);

	public Fusion.Api.SimpleQueryResolver SimpleQueryResolver();

	public Fusion.Api.VirtualQueryResolver VirtualQueryResolver();

	/**
	 * 
	 * @param stream
	 * @param aBOs
	 */
	public boolean XML2BO(Stream stream, ArrayList aBOs);

	/**
	 * 
	 * @param sXML
	 * @param aBOs
	 */
	public boolean XML2BO(String sXML, ArrayList aBOs);

	/**
	 * 
	 * @param reader
	 * @param aBOs
	 */
	public boolean XML2BO(XmlTextReader reader, ArrayList aBOs);

	/**
	 * 
	 * @param stream
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(Stream stream, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur);

	/**
	 * 
	 * @param sXML
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(String sXML, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur);

	/**
	 * 
	 * @param reader
	 * @param aBOs
	 * @param bSkipXMLValidation
	 * @param ur
	 */
	public boolean XML2BO(XmlTextReader reader, ArrayList aBOs, boolean bSkipXMLValidation, UpdateResult ur);

}
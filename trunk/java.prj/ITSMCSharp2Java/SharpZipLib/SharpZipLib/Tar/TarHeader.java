package ICSharpCode.SharpZipLib.Tar;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:57
 */
public class TarHeader extends Object implements ICloneable {

	private Int32 checkSum;
	private static Int32 CHKSUMLEN;
	private static DateTime datetTime1970;
	private static Int32 DEVLEN;
	private Int32 devMajor;
	private Int32 devMinor;
	private static Int32 GIDLEN;
	private static Int32 GNAMELEN;
	private static String GNU_TMAGIC;
	private Int32 groupId;
	private StringBuilder groupName;
	private static byte LF_ACL;
	private static byte LF_BLK;
	private static byte LF_CHR;
	private static byte LF_CONTIG;
	private static byte LF_DIR;
	private static byte LF_EXTATTR;
	private static byte LF_FIFO;
	private static byte LF_GHDR;
	private static byte LF_GNU_DUMPDIR;
	private static byte LF_GNU_LONGLINK;
	private static byte LF_GNU_LONGNAME;
	private static byte LF_GNU_MULTIVOL;
	private static byte LF_GNU_NAMES;
	private static byte LF_GNU_SPARSE;
	private static byte LF_GNU_VOLHDR;
	private static byte LF_LINK;
	private static byte LF_META;
	private static byte LF_NORMAL;
	private static byte LF_OLDNORM;
	private static byte LF_SYMLINK;
	private static byte LF_XHDR;
	private StringBuilder linkName;
	private StringBuilder magic;
	private static Int32 MAGICLEN;
	private Int32 mode;
	private static Int32 MODELEN;
	private DateTime modTime;
	private static Int32 MODTIMELEN;
	private StringBuilder name;
	private static Int32 NAMELEN;
	private Int64 size;
	private static Int32 SIZELEN;
	private static Int64 timeConversionFactor;
	private static String TMAGIC;
	private byte typeFlag;
	private static Int32 UIDLEN;
	private static Int32 UNAMELEN;
	private Int32 userId;
	private StringBuilder userName;
	private StringBuilder version;
	private static Int32 VERSIONLEN;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public TarHeader(){

	}

	private TarHeader(){

	}

	public Object Clone(){
		return null;
	}

	/**
	 * 
	 * @param buf
	 */
	private static Int64 ComputeCheckSum(Byte[] buf){
		return null;
	}

	public Int32 getcheckSum(){
		return checkSum;
	}

	/**
	 * 
	 * @param val
	 * @param buf
	 * @param offset
	 * @param length
	 */
	private static Int32 GetCheckSumOctalBytes(Int64 val, Byte[] buf, Int32 offset, Int32 length){
		return 0;
	}

	public Int32 getCHKSUMLEN(){
		return CHKSUMLEN;
	}

	/**
	 * 
	 * @param dateTime
	 */
	private static Int32 GetCTime(DateTime dateTime){
		return 0;
	}

	/**
	 * 
	 * @param ticks
	 */
	private static DateTime GetDateTimeFromCTime(Int64 ticks){
		return null;
	}

	public Int32 getDEVLEN(){
		return DEVLEN;
	}

	public Int32 getdevMajor(){
		return devMajor;
	}

	public Int32 getdevMinor(){
		return devMinor;
	}

	public Int32 getGIDLEN(){
		return GIDLEN;
	}

	public Int32 getGNAMELEN(){
		return GNAMELEN;
	}

	public String getGNU_TMAGIC(){
		return GNU_TMAGIC;
	}

	public Int32 getgroupId(){
		return groupId;
	}

	public StringBuilder getgroupName(){
		return groupName;
	}

	public byte getLF_ACL(){
		return LF_ACL;
	}

	public byte getLF_BLK(){
		return LF_BLK;
	}

	public byte getLF_CHR(){
		return LF_CHR;
	}

	public byte getLF_CONTIG(){
		return LF_CONTIG;
	}

	public byte getLF_DIR(){
		return LF_DIR;
	}

	public byte getLF_EXTATTR(){
		return LF_EXTATTR;
	}

	public byte getLF_FIFO(){
		return LF_FIFO;
	}

	public byte getLF_GHDR(){
		return LF_GHDR;
	}

	public byte getLF_GNU_DUMPDIR(){
		return LF_GNU_DUMPDIR;
	}

	public byte getLF_GNU_LONGLINK(){
		return LF_GNU_LONGLINK;
	}

	public byte getLF_GNU_LONGNAME(){
		return LF_GNU_LONGNAME;
	}

	public byte getLF_GNU_MULTIVOL(){
		return LF_GNU_MULTIVOL;
	}

	public byte getLF_GNU_NAMES(){
		return LF_GNU_NAMES;
	}

	public byte getLF_GNU_SPARSE(){
		return LF_GNU_SPARSE;
	}

	public byte getLF_GNU_VOLHDR(){
		return LF_GNU_VOLHDR;
	}

	public byte getLF_LINK(){
		return LF_LINK;
	}

	public byte getLF_META(){
		return LF_META;
	}

	public byte getLF_NORMAL(){
		return LF_NORMAL;
	}

	public byte getLF_OLDNORM(){
		return LF_OLDNORM;
	}

	public byte getLF_SYMLINK(){
		return LF_SYMLINK;
	}

	public byte getLF_XHDR(){
		return LF_XHDR;
	}

	public StringBuilder getlinkName(){
		return linkName;
	}

	/**
	 * 
	 * @param val
	 * @param buf
	 * @param offset
	 * @param length
	 */
	public static Int32 GetLongOctalBytes(Int64 val, Byte[] buf, Int32 offset, Int32 length){
		return 0;
	}

	public StringBuilder getmagic(){
		return magic;
	}

	public Int32 getMAGICLEN(){
		return MAGICLEN;
	}

	public Int32 getmode(){
		return mode;
	}

	public Int32 getMODELEN(){
		return MODELEN;
	}

	public DateTime getmodTime(){
		return modTime;
	}

	public Int32 getMODTIMELEN(){
		return MODTIMELEN;
	}

	public StringBuilder getname(){
		return name;
	}

	public String GetName(){
		return "";
	}

	/**
	 * 
	 * @param name
	 * @param nameOffset
	 * @param buf
	 * @param bufferOffset
	 * @param length
	 */
	public static Int32 GetNameBytes(StringBuilder name, Int32 nameOffset, Byte[] buf, Int32 bufferOffset, Int32 length){
		return 0;
	}

	/**
	 * 
	 * @param name
	 * @param buf
	 * @param offset
	 * @param length
	 */
	public static Int32 GetNameBytes(StringBuilder name, Byte[] buf, Int32 offset, Int32 length){
		return 0;
	}

	public Int32 getNAMELEN(){
		return NAMELEN;
	}

	/**
	 * 
	 * @param val
	 * @param buf
	 * @param offset
	 * @param length
	 */
	public static Int32 GetOctalBytes(Int64 val, Byte[] buf, Int32 offset, Int32 length){
		return 0;
	}

	public Int64 getsize(){
		return size;
	}

	public Int32 getSIZELEN(){
		return SIZELEN;
	}

	public String getTMAGIC(){
		return TMAGIC;
	}

	public byte gettypeFlag(){
		return typeFlag;
	}

	public Int32 getUIDLEN(){
		return UIDLEN;
	}

	public Int32 getUNAMELEN(){
		return UNAMELEN;
	}

	public Int32 getuserId(){
		return userId;
	}

	public StringBuilder getuserName(){
		return userName;
	}

	public StringBuilder getversion(){
		return version;
	}

	public Int32 getVERSIONLEN(){
		return VERSIONLEN;
	}

	/**
	 * 
	 * @param header
	 */
	public Void ParseBuffer(Byte[] header){

	}

	/**
	 * 
	 * @param header
	 * @param offset
	 * @param length
	 */
	public static StringBuilder ParseName(Byte[] header, Int32 offset, Int32 length){
		return null;
	}

	/**
	 * 
	 * @param header
	 * @param offset
	 * @param length
	 */
	public static Int64 ParseOctal(Byte[] header, Int32 offset, Int32 length){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setcheckSum(Int32 newVal){
		checkSum = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCHKSUMLEN(Int32 newVal){
		CHKSUMLEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDEVLEN(Int32 newVal){
		DEVLEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdevMajor(Int32 newVal){
		devMajor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdevMinor(Int32 newVal){
		devMinor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGIDLEN(Int32 newVal){
		GIDLEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGNAMELEN(Int32 newVal){
		GNAMELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGNU_TMAGIC(String newVal){
		GNU_TMAGIC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setgroupId(Int32 newVal){
		groupId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setgroupName(StringBuilder newVal){
		groupName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_ACL(byte newVal){
		LF_ACL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_BLK(byte newVal){
		LF_BLK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_CHR(byte newVal){
		LF_CHR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_CONTIG(byte newVal){
		LF_CONTIG = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_DIR(byte newVal){
		LF_DIR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_EXTATTR(byte newVal){
		LF_EXTATTR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_FIFO(byte newVal){
		LF_FIFO = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GHDR(byte newVal){
		LF_GHDR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_DUMPDIR(byte newVal){
		LF_GNU_DUMPDIR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_LONGLINK(byte newVal){
		LF_GNU_LONGLINK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_LONGNAME(byte newVal){
		LF_GNU_LONGNAME = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_MULTIVOL(byte newVal){
		LF_GNU_MULTIVOL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_NAMES(byte newVal){
		LF_GNU_NAMES = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_SPARSE(byte newVal){
		LF_GNU_SPARSE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_GNU_VOLHDR(byte newVal){
		LF_GNU_VOLHDR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_LINK(byte newVal){
		LF_LINK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_META(byte newVal){
		LF_META = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_NORMAL(byte newVal){
		LF_NORMAL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_OLDNORM(byte newVal){
		LF_OLDNORM = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_SYMLINK(byte newVal){
		LF_SYMLINK = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLF_XHDR(byte newVal){
		LF_XHDR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setlinkName(StringBuilder newVal){
		linkName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setmagic(StringBuilder newVal){
		magic = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAGICLEN(Int32 newVal){
		MAGICLEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setmode(Int32 newVal){
		mode = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMODELEN(Int32 newVal){
		MODELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setmodTime(DateTime newVal){
		modTime = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMODTIMELEN(Int32 newVal){
		MODTIMELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setname(StringBuilder newVal){
		name = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNAMELEN(Int32 newVal){
		NAMELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setsize(Int64 newVal){
		size = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSIZELEN(Int32 newVal){
		SIZELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTMAGIC(String newVal){
		TMAGIC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void settypeFlag(byte newVal){
		typeFlag = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUIDLEN(Int32 newVal){
		UIDLEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUNAMELEN(Int32 newVal){
		UNAMELEN = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setuserId(Int32 newVal){
		userId = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setuserName(StringBuilder newVal){
		userName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setversion(StringBuilder newVal){
		version = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setVERSIONLEN(Int32 newVal){
		VERSIONLEN = newVal;
	}

	/**
	 * 
	 * @param outbuf
	 */
	public Void WriteHeader(Byte[] outbuf){

	}

}
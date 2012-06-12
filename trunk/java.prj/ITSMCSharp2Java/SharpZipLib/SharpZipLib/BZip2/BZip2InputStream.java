package ICSharpCode.SharpZipLib.BZip2;
import ICSharpCode.SharpZipLib.Checksums.IChecksum;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-ËÄÔÂ-2010 17:16:45
 */
public class BZip2InputStream extends Stream {

	private Int32 baseArray[][];
	private Stream baseStream;
	private boolean blockRandomised;
	private Int32 blockSize100k;
	private Int32 bsBuff;
	private Int32 bsLive;
	private Int32 ch2;
	private Int32 chPrev;
	private Int32 computedBlockCRC;
	private UInt32 computedCombinedCRC;
	private Int32 count;
	private Int32 currentChar;
	private Int32 currentState;
	private Int32 i2;
	private boolean inUse[];
	private Int32 j2;
	private Int32 last;
	private Int32 limit[][];
	private byte ll8[];
	private IChecksum mCrc;
	private Int32 minLens[];
	private Int32 nInUse;
	private static Int32 NO_RAND_PART_A_STATE;
	private static Int32 NO_RAND_PART_B_STATE;
	private static Int32 NO_RAND_PART_C_STATE;
	private Int32 origPtr;
	private Int32 perm[][];
	private static Int32 RAND_PART_A_STATE;
	private static Int32 RAND_PART_B_STATE;
	private static Int32 RAND_PART_C_STATE;
	private Int32 rNToGo;
	private Int32 rTPos;
	private byte selector[];
	private byte selectorMtf[];
	private byte seqToUnseq[];
	private static Int32 START_BLOCK_STATE;
	private Int32 storedBlockCRC;
	private Int32 storedCombinedCRC;
	private boolean streamEnd;
	private Int32 tPos;
	private Int32 tt[];
	private byte unseqToSeq[];
	private Int32 unzftab[];
	private byte z;

	public BZip2InputStream(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param stream
	 */
	public BZip2InputStream(Stream stream){

	}

	private static Void BadBlockHeader(){

	}

	private static Void BlockOverrun(){

	}

	private Int32 BsGetint(){
		return 0;
	}

	private Int32 BsGetInt32(){
		return 0;
	}

	/**
	 * 
	 * @param numBits
	 */
	private Int32 BsGetIntVS(Int32 numBits){
		return 0;
	}

	private char BsGetUChar(){
		return 0;
	}

	/**
	 * 
	 * @param n
	 */
	private Int32 BsR(Int32 n){
		return 0;
	}

	/**
	 * 
	 * @param f
	 */
	private Void BsSetStream(Stream f){

	}

	public boolean CanRead(){
		return false;
	}

	public boolean CanSeek(){
		return false;
	}

	public boolean CanWrite(){
		return false;
	}

	public Void Close(){

	}

	private Void Complete(){

	}

	private static Void CompressedStreamEOF(){

	}

	private static Void CrcError(){

	}

	private Void EndBlock(){

	}

	private Void FillBuffer(){

	}

	public Void Flush(){

	}

	private Void GetAndMoveToFrontDecode(){

	}

	/**
	 * 
	 * @param limit
	 * @param baseArray
	 * @param perm
	 * @param length
	 * @param minLen
	 * @param maxLen
	 * @param alphaSize
	 */
	private Void HbCreateDecodeTables(Int32[] limit, Int32[] baseArray, Int32[] perm, Char[] length, Int32 minLen, Int32 maxLen, Int32 alphaSize){

	}

	private Void InitBlock(){

	}

	private Void Initialize(){

	}

	public Int64 Length(){
		return null;
	}

	private Void MakeMaps(){

	}

	public Int64 Position(){
		return null;
	}

	/**
	 * 
	 * @param b
	 * @param off
	 * @param len
	 */
	public Int32 Read(Byte[] b, Int32 off, Int32 len){
		return 0;
	}

	public Int32 ReadByte(){
		return 0;
	}

	private Void RecvDecodingTables(){

	}

	/**
	 * 
	 * @param offset
	 * @param origin
	 */
	public Int64 Seek(Int64 offset, SeekOrigin origin){
		return null;
	}

	/**
	 * 
	 * @param newSize100k
	 */
	private Void SetDecompressStructureSizes(Int32 newSize100k){

	}

	/**
	 * 
	 * @param val
	 */
	public Void SetLength(Int64 val){

	}

	private Void SetupBlock(){

	}

	private Void SetupNoRandPartA(){

	}

	private Void SetupNoRandPartB(){

	}

	private Void SetupNoRandPartC(){

	}

	private Void SetupRandPartA(){

	}

	private Void SetupRandPartB(){

	}

	private Void SetupRandPartC(){

	}

	/**
	 * 
	 * @param array
	 * @param offset
	 * @param count
	 */
	public Void Write(Byte[] array, Int32 offset, Int32 count){

	}

	/**
	 * 
	 * @param val
	 */
	public Void WriteByte(byte val){

	}

}
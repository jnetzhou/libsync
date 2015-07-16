数据同步算法（详细请参考http://blog.csdn.net/liuben/archive/2010/08/06/5793706.aspx）<br>
假设现在有两台计算机Alpha和Beta ,计算机Alpha能够访问A文件,计算机Beta能够访问B文件，文件A和B非常相似，计算机Alpha和Beta通过低速网络互联。基于dedupe技术的数据同步算法大致流程与Rsync相似，简单描述如下：<br>
1、Beta采用数据切分算法，如FSP(fixed-size partition)、CDC(content-defined chuking)，将文件B分割成大小相等或不等的数据块；<br>
2、Beta对于每一个数据块,计算一个类似rsync弱校验值和md5强校验值，并记录数据块长度len和在文件B中的偏移量offset；<br>
3、Beta将这将数据块信息发送给Alpha；<br>
4、Alpha采用同样的数据块切分技术将文件A切成大小相等或不等的数据块，并与Beta发过来的数据信息进行搜索匹配，生成差异编码信息；<br>
5、Alpha将差异编码信息发送给Beta，并同时发送重构文件A的指令；<br>
6、Beta根据差异编码信息和文件B重构文件A。<br>
上面算法描述中，有几个关键问题需要解决，即文件切分、切分数据块信息描述、差异编码、差异编码信息描述、文件同步。<br><br>

libsync函数库由提供三个API，原型描述如下：<br>
1、int file_chunk(char <b>src_filename, char</b>chunk_filename, int chunk_algo)<br>
功能：对件进行切分生成分块描述文件。<br>
参数：src_filename为源文件，chunk_filename为生成的块信息描述文件，chunk_algo为文件切分算法，目前支持FSP、CDC、SB三种。<br><br>

2、int file_delta(char <b>src_filename, char</b>chunk_filename, char <b>delta_filename, int chunk_algo)</b><br>
功能：使用生成的块描述信息对文件进行差异编码。<br>
参数：src_filename为待编码文件，chunk_filename为通过函数file_chunk生成的块描述文件，chunk_algo为文件切分算法。<br><br>

3、int file_sync(char <b>src_filename, char</b>delta_filename)<br>
功能：使用差异编码文件将源文件同步至目标文件。<br>
参数：src_filename为基本文件，delta_filename为通过函数file_delta生成的差异编码文件。<br><br>

数据同步有PULL和PUSH两种应用模式，PULL是将远程数据同步到本地，而PUSH是将本地数据同步到远程。对应到同步算法，主要区别在于数据分块和差异编码位置不同。PULL和PUSH同步模式步骤分别如下所述。<br>
PULL同步模式流程：<br>
1、本地对文件A进行数据切分，生成数据块描述文件chunk；<br>
2、上传chunk文件至远程服务器；<br>
3、远程服务器对文件B进行差异编码，生成差异编码文件delta；<br>
4、下载delta文件至本地；<br>
5、本地同步文件A至文件B，相当于下载文件B到本地文件A。<br><br>


PUSH同步模式流程：<br>
1、远程服务器对文件B进行数据切分，生成数据块描述文件chunk；<br>
2、下载chunk文件至本地；<br>
3、本地对文件A进行差异编码，生成差异编码文件delta；<br>
4、上传delta文件至远程服务器；<br>
5、远程同步文件B到A，相当于上传文件A到远程文件B。<br>
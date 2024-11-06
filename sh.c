#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
>>> echo h; ls
>>> cat README | grep xv6
Execution of pipe failed
xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".
ELF�Z@`�@8@pg�S��  Q�tdyq�"�&�J�N�R�*�����
���N������˅�'�'��I��E�pt�dBi�ijEa��G=�A�"���F�c��@���E���c
                                                          �E��`dA��.��%:��������ƃ���Eŷ�5ٿ����_��E���"�&�J�*���G��c
                                  ���J�����������1�����E�`Bd�dia��]q���&�J�N�R�V�Z�^�b���.�J�
             �?������5���EJ��`���#�ʅN����uѩG#���;&AʅE� 8�cE@;�KA��JZ��`6cY�;
                                                                            �

�J#�V�]���3
�@;
LAR�ʅ�'ɷ�`d�tBy�yz�jBk�klaa��yq�"�&�J�N�R��Gc֧���Gcۧ��	����	�������E5	�`0��c@��R����&���-!	�9�E�`*����	E��hE� )�ER�����E�@(�5	���@iE��&A�"��?�E��%A"�����������u�"dA��A"�G���c���G���;��@"dA��A"�G����������e�;��@%"dA��E�A"ʪ��3�#������"dA��A"�G��c���G��E"dA��E�q������N�R�V�Z�^���.�*��D�J5K���$c�DF���E�`c^��G��#�c�W	�g������ޙ#�	^��`Fd�di�yBz�z{�k%a���"�J�.��E� cB&䪄ʅ��*�&��@�dJ��`Bdia��}YͿA"�F������%Fch�*�E�%��������F�������q��"dA��E�A"ct�c_����*�������������"dA��3����Z���������������}��#����ɿA"ʛ���������G�c������E�;��@"dA��E�A�"����`dA���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���Hs���"����F�������`Bda��9q�"�&�����c�%�H��G&�R:�'����������#������������c��3������Z�J�N��3��������}7����@�E��&����}��9�y�i�pBt�t!a����@�H��q�������c    &��N�R�V�Z�^�b�f�*�.����I�DG�
P
 @�
   ��ʅZ�����c�Y�$&����c
                       	 �	�	��W���ͷ����6���R�F'c��c��Pc���c��c��0c��Pc���PZ����II����F)F��
                      Z����ʋ�I���@c����c���Pc��
��c���PZ���?�ʅZ����I�����F)F��
                              Z���?�$ʋ�I-��@c��Pc	���������FAF��
                                                                      Z����$ʋ�I����F)F��
        Z���߉$ʋ�I�����F)F��
                           Z�����ʋ�Iٵ���F)F��
                                             Z���_܅$ʋ�Iu����F)F��
                                                                 Z���ډ$ʋ�II����FAF��
    Z����ʋ�I�����FAF��
                      Z���ׅ$ʋ�I��j�����
                                      �Z����ӓ�Z���_�AI�
                                                       ��+)���ޗ��Z���ђ	}9�	�ꋁIm!�����
          c	�E	��Z���?�	�E	��΋�Iͻ		�#��ŷ΋�I���d�yBz�z{�kBl�l�`Fdi%a��]q�"�����#0#4#4��"�����`Bdaa��q�"�
                                                    �����#8#<�#4����E����`Bd%a����#8���G���>������#;�f"dA��9q�"�&�N����������5�d�a�GczJ�R�V�Z�N��6��    �fcs�j

�J		�a�Z��J�R�V�Z������#0�`��#����cᩨ#$eA���5	-�a�Gcr�7	>����R���?��U�EyBj�jk=�yBj�jk���;7A�Ǔ����#�7#9�X��pBt�t�i!a��yBj�jk��usage: grep pattern [file ...]
grep: cannot open %s
����JB0L����6789ABCDEFzR|
�
 B
 l�B�
     0B�B�B�B�B,P���vHD��B
                         n
�B�
   BB
��,�T���FB H���B
               p�B�
                    B�B�BD�j����BPT����
�
 ����B
     ��B�
         PB�B�B�B�B�B�B�B�B(������B0L����
�
 B
 $J���BD��B
           D<���BB�B
                   R�
                     B h4���,BB�B
                                b�
                                  B$�<���*BB�B
                                             \
�
 BB
    �>���"BB�B
             X�
               B$�<���$BB�B
                          V
�
 BB
   @8���pB`R����
�
 ���B
    F�B�
        `B�B�B�B�B�B�B�B0Dd���:B F��B
                                    N�R�D
�B�
    B�BB
        $xj���HBB�B
                  z
�
 BB
   $�����XBB�B
             d
�
 BB
   $�����:BB�B
             l
�
 BB
   (�����BD��B
             F�B�
                 B$d���B D��B
                            P�B�
                                 B4DZ����B@F���B
                                               d�
f�B�B
�B�
   @B�BB
        T|�����B`F��B
                    X��
�
 �������D�>�B�B�B�B�B�B�B�B�B�
                              `B�B$�����*BPD��B
                                              0\�B�
                                                   PB$�����2B`D��B
                                                                 @d�B�
                                                                      `B $����BB�B
 x�
   B|Hd����B@H����
B
j�
  ��b����^
�
 ��B
    F�
      ��p
�B�B�B�B
        B�B�B�B�f�B�
����                @B�B�BB
�
 ��B�B�B�B��
            �EZ��int�hhB@hbuW  �
I�	I
�"�	�

I�      I	I
�!	I	�
                �	I6	I	6	I
6[	6	[	I
                        ��	�	h
                                        I�	I	[	I-cIJccItrec��c&�
�+I���Z�[y�Z��&I�Z���&��[�Z#\�[�Z�Z#[�[#~II���reI
I�&��fd(IJi(
            I��)	�
                         ��[0��Z�[y��Zy"��Z00�Z2[	�
6�-Z1>�JZ�[0D�aZ0T��Z	�
Z�Z1
   �
    �B�

       ��fd
           nIm
�c	>b-Z�[:N�KZ�[�f�qZ1[�\y�z�Z�[��"\���8Z�[�\�[�
                                                     AEZ��,9��7��dev�#in-#Y    �e		�#
k

Z#int�
��	&�
          	�	

�/	/	�
@
 �	�d	�	d	�
��	��
dst�d     ��R�d���	
Yrc�
n�)-�
��Z�Z[�[\�\
���n��
Ss1�
�s2�$
 n�--
     p1�/�
          p2�/[
ndn�
dstp�7nd�=srcq/[
5<c���@sc/!ne��'U�����nU/hstU"
                              �fdW�rX�_��Z�Z[0���Zy[���ZyC�$���bufC
                                                                   ��maxC�AiE��ccE                                               1	�Zi2��%-��;vs%/�n'�:�����l��q#/P0[x�\1:�$7�s:/��c:5[^/d�2�dst/dZ�c/�[n/-�
    s��t/0os	�Z1
Zlf�
    �=f�lfZ0�
�lpE|��
       �El	n
�       �        ,9�7�int����go���	�

a�
  a
   �
    a
��� �   �Mfmt�M)ap�
                   ���	�Z1[�Z\�H
a�fmt�M$�ap�                    ���u�fd�
a��fmt4Mp4*�k6���ic07a�c1742]��fd4
                          ac27aui7a� �7a_!�_   ��"��"��"��Z�0��Z�x�Z�[
<%�"�v�&Z�[���DZ�[���fZ�\:]1.��Z�[�6��Z�[�L��Z�\:]1~��Z�\@]0�Z�\:]1��*Z�\:]0��LZ�\:]0��nZ�\:]0���Z�\@]��Z�\@]0�Z�
                                ���*�d*a*Ni+a��2L#�fda�#xxa5$�a�$sgn(a�$bu��@ia/%neg
a�%-�%�Zy��Z�
l�B&fd

a�&c
��&��Z�Z[xo\1a�
               �E	�
W,9��int�=	%
�#k              �ptr
-#
�	sv	x	c
���
   ��	
        �	
�
U
@
@��	�
-�'pB
     ��'7B��(-8)��	W��)�)E* 
>
Z�./�u/-p1	hp2
                   �C	�	}*ap
                                    �Zbp
                                        �*p_%



                                             $

                                              >
                                              I!I/&I:
                                                     ;
                                                      9
                                                       I?

.?
  :
   ;
    9
     '
      I<
        	I
.?
  :
   ;
    9
     '
      <




.?     I
  :
   ;
    9
     '
      I�
        <


         &.?
            :
             ;
              9
               '
                I@�B
                   :
                    ;
                     9
                      I:
                        ;
                         9
                          I��1��
�B
��1:
    ;
     9
      I4:
         ;
          9
           I.?
              :
               ;
                9
                 '
                  @�B
                     %

                      ;
                       9
                        I$

                          >


                           :
                            ;
                             9
:
 ;
  9
   I8
:
 ;
  9
   I8
$

 >
.?
  :
   ;
    9
     '
      I<
        	I


I
 &I


.?
  :
   ;
    9
     '
      I�
        <
         .?
           :
            ;
             9
              I<
                .?
                  :
                   ;
                    9
                     '
                      I@�B
                         :
                          ;
                           9
                            I��1��
�B
&:
  ;
   9
    I:
      ;
       9
        I
:
 ;
  9
   I
:
 ;
  9
   I��1:
        ;
         9
          I
:
 ;
  9
   I
.?
  :
   ;
    9
     @�B
        ��1

           ;
            9
             I$

               >
                $

                 >


                 I!I/
                    &I	4:
                          ;
                           9
                            I

.?
  :
   ;
    9
     '
      I<

        I


&.?      I
   :
    ;
     9
      '
       @�B
         :
          ;
           9
            I:
              ;
               9
                I
��1��
�B
:
 ;
  9
   I4:
      ;
       9
        I1X
           Y
            W
             141��1�.:
                      ;
                       9
                        '
                          

                         ;
                          9
                           I:
                             ;
                              9
                               I.:
                                  ;
                                   9
                                    '
                                     @�B
                                        :
                                         ;
                                          9
                                           I.:
                                              ;
                                               9
                                                '
                                                 @�B
                                                    %

                                                     ;
                                                      9
                                                       I$

                                                         >
                                                          $

                                                           >


                                                           :
                                                            ;
                                                             9
:
 ;
  9
   I8
:
 ;
  9
   I8


:
 ;
  9
:  	
 ;
  9
   I


I
 4:
   ;
    9
     I

.?
  :
   ;
    9
     '
      I<
I.?
   :
    ;
     9
      '
       I@�B
           :
            ;
             9
              I:
                ;
                 9
                  I4:
                     ;
                      9
                       I1RUX
                            Y
                             W
                              1
                               U41��1��1��
�B


�.:
   ;
    9
     '
      I 

       ;
        9
         I:
           ;
            9
             I.?
                :
                 ;
                  9
                   '
                    @�B
                      :
                       ;
                        9
                         I
:
 ;
  9
   I
rr0>x>Hr0HJr�Z�BbBJ�Z��[�DcDJ�[��\�@YJRrRXrX�x��r��r��x��rJtZt�_���Z���Z��_���Z���Z��_��Z��_���Z���Z���Z�J�[���[���[��\���[���[��{����[���[��r��r ��x�r r��Z��b��Z�b�Z���[�Y��r��r0�Zx��Z�"�Z�",Z,6�Z�6:Z:Z�Z���[��{h��"�[�"*[*6�[�68[8Z�[�
��[@3%#��"d6Zr��x��r���r2Z2�c���Z�2[2�f���[�z�Z��Z"20�2lhl�d��h��       ������d2lb��
���b26Y@lY��YNPrPVrV^x^`r`brNYZYb�Z�NY[Yb�[�NY\Yb�\�r�r�FxFHrHJrJNx(Z(J�Z�JLZLN�Z�([(J�[�JN[�\� |� "]"(|�(D�\1�JN|��>Z@DZJLZLN�Z���r��r��x��r��r�x��[���[���[��[���\���\1���\��\1���Z��^��Z�^tvrvzrz�x��r��r��xt�Z��^��Z���Z�z�0���Z��P���0�:<r<Dr Djxjnr nprptx:KZKt�Z�:H[H\b\p�[�prbrt�[�LYZYdYptZ\db��r��r��(x(8r�8:r��Z�6g6:Z��[�0d0:�[���0���Y�c�����cZ��r��r��x��r��r��x��Z��Z��Z���Z���r��r��x��r��r��\���\���0���z��z#��z#�Z\r\`r`|x|~r~�r��xZhZhxz�x��Z���Z���Z�`j0�jz#�n}z#���0�.0r04r4VxVXrXZr.DZDPZ.F[FZ[rr*x*,r,.r�Z�._[.[xxzrz�r���x���r���rx�Z��[���Z�NPrPVr�Vtx0tvr�vxrNoZox�Z�No[ox�[���r��r��HxHLr�LNr�Z>f>N�Z��[:d:N�[��\�g��b��g��b�g�b�g4b48g8LbLPgPfbfjgj�b��g��b��g��b��g��j��g�c g 2c2@g b.4b	_	
                                                                b
                                                                 _${_{�b��_��_��b�b�b4E_LPbfjb��_��b��_��b�
�~"#���>~���0B0�B{\��\��\��\\�"\4<\LT\fn\��\��\��\�
                                                   \ 4\�0�Y �Y�Y�.Y4`YfzY��Y�4Y�
                                                                               0�
 (c(00�0~c��c��c��c�c�2c4JcLdcf~c��c��c��c��c48c��c��f��0���@����A�� r (r�(�x��r���r��xDZD�Y���Z���Z4[4��[���[���[��\���\���\8]8��]���]4D0�FH~�Hl^l�����~�*40�4�a��1�2b[bp|���[�r�x�r rZ�Z�[{��r��r��hxhnr�nprpzx��Z�z�Z���_��
��_Z"_"$Z$'_8d_pzZ��Z��Z��
��ZZ8dZ�lclp�  %#4%#�pzc
                        �����

�����+(�".
          �����

�����+(�Z	zp�(.ZZ	zp�rr~x~�r��r
.].0zp�0r]r�zp�Z,Zb,
                   ��,J
                      l�,b      z�0�
user./usergrep.cuser.h	�%	}			
				%			l			
				
	~		
       !~		z	
                               					
	}			

	z	
               	j				
                                                				|
                                                                              	�
                                                                               +
			!z		!	
	
		
			
                        							0t		0				
                                               			
						
                                                		
						
                                                				�
                                                                              z%N�
user./kernel./userulib.ctypes.hstat.huser.h	Z
								
                                                                		

                                                                              	



				
		
			}							
										
		
			�				{	
		
                					
		
					
                                        					
		
                |	
                       								
		
					
                                        	|				}

                                                                              	{
	{			
			
		       ��
userusys.S	�								���
user./kernel/usr/lib/gcc-cross/riscv64-linux-gnu/13/include./userprintf.ctypes.hstdarg.huser.h	l
	
        	
	
        					
			{	x				
						
		 
	
q	
							
								�		x

	x				
"										~
�	�					
						
?                                               		
        B	(					
,                                                       		
        U		o					
<                                                               		
9       E	I					
7                                                       		
        J							
4                                                               		
1       M	Q					
/                                                       		
        R			L		
	
					,	
)               Y                               0			1	
                                	
'       Z              ~                			~	
					�	       �G�
user./kernel./userumalloc.ctypes.huser.h					w!	{		'							
				
						
                                                		%	)	
					
                                        		i	
                                                                	
 	a	
                								l
				(			
                                                        		
                                                                        	
Z							!	t		

				opengrepmemmoveexitstrchrtextmatchherematchstarunsigned char/uolstore/home/users/sc23k2m/comp2211/xv6_riscv_comp2211matchlong unsigned intshort unsigned intwritemainreadGNU C17 13.2.0 -mcmodel=medany -mabi=lp64d -misa-spec=20191213 -march=rv64imafdc_zicsr_zifencei -ggdb -gdwarf-2 -O -fno-omit-frame-pointer -fno-common -fno-builtin-strncpy -fno-builtin-strncmp -fno-builtin-strlen -fno-builtin-memset -fno-builtin-memmove -fno-builtin-memcmp -fno-builtin-log -fno-builtin-bzero -fno-builtin-strchr -fno-builtin-exit -fno-builtin-malloc -fno-builtin-putc -fno-builtin-free -fno-builtin-memcpy -fno-builtin-printf -fno-builtin-fprintf -fno-builtin-vprintf -fno-stack-protector -fno-pieargcuser/grep.cpatternfprintfshort intargvclosememcmpuint64vsrcstrlenstrcpygetsucharstrcmpfstatuintstartvdstatoiuser/ulib.ccdstmemcpytypememsetnlinksizeuser/usys.SGNU AS 2.42__builtin_va_liststateuser/printf.cputcvprintf__gnuc_va_listprintintbasedigitsprintptrnbytesuser/umalloc.cHeadersbrkmallocnunitsfreepheaderlong intmorecoreprevpAlignfreeGCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0ARriscvHrv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0_zmmul1p0����",�
�
	


�J�ZQ��X��alf��o�
v��     ��l�2�X�Jv�
�n: �%L*\1�"8��=JG�,N<R��:V�F$\�aZg�Hl�*sx$,���2�grep.c$xrv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0_zmmul1p0ulib.cusys.oprintf.cputcprintintdigitsumalloc.cfreepbasestrcpymemmovematchheremknodgetsgetpidmemcpygrepmallocsleepgetyearpipewritefstatfprintfkillvprintfchdirexecwaitreadunlinkmemcmpforksbrkuptimememsetmainmatchstarstrcmpdupbufmatchexitstartatoistrlenopenstrchrmkdirclosefree.symtab.strtab.shstrtab.text.rodata.eh_frame.data.bss.debug_info.debug_abbrev.debug_loc.debug_aranges.debug_line.debug_str.comment.riscv.attributes.debug_ranges
!�
��)�
��3  > �J�4�X};Q+c�f�r�g9~0�H�0A�&�pg�S���P�    �����cat: cannot open xv6
>>> 



/* Read a line of characters from stdin. */
int getcmd(char *buf, int nbuf) {
    printf(">>> ");  // Display the prompt
    int i = 0;
    char c;
    while (i < nbuf - 1) {
        if (read(0, &c, 1) != 1)  // Read one byte from stdin
            break;
        if (c == '\n')  // If a newline is encountered, stop
            break;
        buf[i++] = c;
    }
    buf[i] = '\0';  // Null terminate the string
    return i;
}

/*
  A recursive function which parses the command
  at *buf and executes it.
*/
__attribute__((noreturn))
void run_command(char *buf, int nbuf, int *pcp) {

    char *arguments[10];
    int numargs = 0;
    int ws = 1, we = 0;
    int redirection_left = 0, redirection_right = 0;
    char *file_name_l = 0, *file_name_r = 0;
    int pipe_cmd = 0, sequence_cmd = 0;

    /* Parse command character by character */
    for (int i = 0; i < nbuf; i++) {
        char c = buf[i];

        if (c == '\0' || c == '\n') {
            if (!ws) {
                buf[i] = '\0';
                arguments[numargs++] = &buf[we];
            }
            break;
        }

        if (c == '<') {
            redirection_left = 1;
            buf[i] = '\0';
            while (buf[i + 1] == ' ' || buf[i + 1] == '\t') i++;
            file_name_l = &buf[i + 1];
            continue;
        } else if (c == '>') {
            redirection_right = 1;
            buf[i] = '\0';
            while (buf[i + 1] == ' ' || buf[i + 1] == '\t') i++;
            file_name_r = &buf[i + 1];
            continue;
        }

        if (!redirection_left && !redirection_right) {
            switch (c) {
                case ';':
                    buf[i] = '\0';
                    sequence_cmd = 1;
                    break;
                case '|':
                    buf[i] = '\0';
                    pipe_cmd = 1;
                    break;
                default:
                    if (c != ' ' && c != '\t') {
                        if (ws) { ws = 0; we = i; }
                    } else if (!ws) {
                        buf[i] = '\0';
                        arguments[numargs++] = &buf[we];
                        ws = 1;
                    }
                    break;
            }
        }
    }

    if (sequence_cmd) {
        if (fork() == 0) {
            run_command(&buf[we + 1], nbuf - we - 1, pcp);
        } else {
            wait(0);
        }
        exit(0);
    }

    if (redirection_left) {
        int fd = open(file_name_l, O_RDONLY);
        if (fd < 0) {
            fprintf(2, "Error opening input file: %s\n", file_name_l);
            exit(1);
        }
        close(0);
        dup(fd);
        close(fd);
    }
    if (redirection_right) {
        int fd = open(file_name_r, O_WRONLY | O_CREATE);
        if (fd < 0) {
            fprintf(2, "Error opening output file: %s\n", file_name_r);
            exit(1);
        }
        close(1);
        dup(fd);
        close(fd);
    }

    if (numargs > 0 && strcmp(arguments[0], "cd") == 0) {
        if (numargs < 2) {
            fprintf(2, "cd: no directory specified\n");
        } else {
            write(pcp[1], arguments[1], strlen(arguments[1]) + 1);
            exit(2);
        }
    } else if (pipe_cmd) {
        int p[2];
        pipe(p);
        if (fork() == 0) {
            close(1);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            exec(arguments[0], arguments);
            fprintf(2, "Execution of %s failed\n", arguments[0]);
            exit(1);
        }
        if (fork() == 0) {
            close(0);
            dup(p[0]);
            close(p[1]);
            run_command(&buf[we + 1], nbuf - we - 1, pcp);
        }
        close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
    } else {
        exec(arguments[0], arguments);
        fprintf(2, "Execution of %s failed\n", arguments[0]);
        exit(1);
    }
}

int main(void) {
    static char buf[100];
    int pcp[2];
    pipe(pcp);

    while (getcmd(buf, sizeof(buf)) >= 0) {
        if (fork() == 0) {
            run_command(buf, 100, pcp);
        }
        int child_status;
        wait(&child_status);
        if (child_status == 2) {
            char new_dir[100];
            if (read(pcp[0], new_dir, sizeof(new_dir)) > 0) {
                if (chdir(new_dir) < 0) {
                    fprintf(2, "chdir to %s failed\n", new_dir);
                }
            }
        }
    }
    exit(0);
}

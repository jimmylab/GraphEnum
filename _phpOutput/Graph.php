<?php
!defined('GraphRequired') && exit('<h1>Illegal Request!</h1>');
class Graph {
	protected $edges = 5;

	protected $radius = 250;

	protected $center = array();
	protected $vertexes = array();
	protected $canvas = null;

	protected static $MinSideLen = 30;
	public static $Margin = 15;
	public static $PointSize = 12;
	protected static $BgColor = array(50, 143, 245);    //#328ff5

	public function __construct( $edges, $radius = 0 ) {
		$this->edges = $edges;
		$this->radius = ($radius<=0) ? $this->radius : $radius;
		$this->setCircle();
		$this->createVertexes();
	}

	public function drawGraph( $filename='' ) {
		if ( extension_loaded('gd') && function_exists('imagepng') ) {
			if ( $filename=='' && !defined('IS_DEBUG') ) header("Content-type: image/png");
			if ($filename!='' ) imagepng( $this->canvas, $filename.'.png' );
			else imagepng( $this->canvas );
			imagedestroy( $this->canvas ); $this->canvas = null;
		} else echo '<h1>Fatal Error</h1>
		<p><strong>Failed to render image:</strong> Cannot Load GD Library.</p>';
	}

	public function graphApply( &$matrix, $reverse=false ) {
		if ( extension_loaded('gd') && function_exists('imagecreate') ) {
			$this->createCanvas();
			$this->drawLines( $matrix, $reverse );
			$this->drawVertexes();
		} else echo '<h1>Fatal Error</h1>
		<p><strong>Failed to render image:</strong> Cannot Load GD Library.</p>';
	}

	public function Radius( $newRadius = 0 ) {
		if ( $newRadius != 0 ) {
			$this->radius = $newRadius;
			$this->setCircle();
			$this->createVertexes();
			$this->canvas = null;
		}
		return $this->radius;
	}

	public function setBgColor($color) {
		self::$BgColor = hex2rgb($color);
	}

	public function __destruct() {
		//if ( $this->canvas != null ) imagedestroy( $this->canvas );
	}


	protected function setCircle() {
		$n = $this->edges; $r = $this->radius;
		$sideLen = 2*$r*sin(pi()/$n);
		if ( $sideLen < self::$MinSideLen ) $this->radius = $r = (int)( self::$MinSideLen/2/sin(pi()/$n) )+1;
		$this->center = array(self::$Margin+$r, self::$Margin+$r);
	}
	public function createVertexes() {
		$this->vertexes = array(); $n = $this->edges; $r = $this->radius;
		$offset_x = $this->center[0]; $offset_y = $this->center[1];
		for ( $k=0; $k<$n; $k++ ) {
			$angle = (4*$k - $n)/2/$n*pi();
			$this->vertexes[]= array( 
				$r*cos($angle)+$offset_x, 
				$r*sin($angle)+$offset_y );
		}
		return $this->vertexes;
	}

	protected function createCanvas() {
		$len = 2*$this->radius+2*self::$Margin;
		$this->canvas = imagecreatetruecolor($len, $len);
		$bg = imagecolorallocate($this->canvas, self::$BgColor[0], self::$BgColor[1], self::$BgColor[2]);
		imagefill($this->canvas, 0, 0, $bg);
		imageantialias($this->canvas, true);
	}
	protected function drawLines( $matrix, $reverse=false ) {
		$matrix = explode(' ', $matrix);
		$color = imagecolorallocate($this->canvas, 0, 0, 0);
		for ( $i=0; $i<$this->edges; $i++ ) {
			for ( $j=$i+1; $j<$this->edges; $j++ ) {
				if ( ($matrix[$i][$j]!='1') ^ $reverse ) continue;
				$a = $this->vertexes[$i];
				$b = $this->vertexes[$j];    //Outbound: $b = $this->vertexes[($i+1)%$this->edges];
				imageline($this->canvas, $a[0], $a[1], $b[0], $b[1], $color);
				//imagethickline($this->canvas, $a[0], $a[1], $b[0], $b[1], $color, 3);
			}
		}
	}
	protected function drawVertexes() {
		$color = imagecolorallocate($this->canvas, 0, 0, 0);
		for ( $i=0; $i<$this->edges; $i++ ) {
			$point = $this->vertexes[$i];
			imagefilledellipse($this->canvas, $point[0], $point[1], self::$PointSize, self::$PointSize, $color);
		}
	}

}

function _RequestInt( $key, $default=0 ) {
	if ( isset($_REQUEST[$key]) ) return intval($_REQUEST[$key]);
	else return $default;
}

// #ff00ff -> array(255,0,255) or #f0f -> array(255,0,255)
function hex2rgb($color) {
	$color = strtolower($color);
	$color = str_replace('#','',$color);
	$s = strlen($color) / 3;
	$rgb[]=hexdec(str_repeat(substr($color,0,$s),2/$s));
	$rgb[]=hexdec(str_repeat(substr($color,$s,$s),2/$s));
	$rgb[]=hexdec(str_repeat(substr($color,2*$s,$s),2/$s));
	return $rgb;
}
function imagethickline(&$canvas, $x1, $y1, $x2, $y2, $color, $thick) {
	$thick = round($thick);
	if ($thick>1) {
		for ( $i=1; $thick>1; $i++, $thick-=2 ) {
			imageline($canvas, $x1+$i, $y1, $x2+$i, $y2, $color);
			imageline($canvas, $x1, $y1-$i, $x2, $y2-$i, $color);
		}
	} return imageline($canvas, $x1, $y1, $x2, $y2, $color);
}

?>
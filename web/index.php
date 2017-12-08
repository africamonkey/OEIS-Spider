<h2>soj.monke.top</h2>
<h3>0-85000</h3>
<p>
<?php

$t = file_get_contents("/home/africamonkey/Downloads/oeis/end.txt");
$end = intval($t);
$t = file_get_contents("/home/africamonkey/Downloads/oeis/begin.txt");
$start = intval($t);
$t = file_get_contents("/home/africamonkey/Downloads/oeis/lastans.txt");
$a = intval($t);
echo ($a - $start + 1);
echo '/';
echo ($end - $start);
?>
</p>

<p>
<?php
echo round((double)($a - $start + 1) / ($end - $start) * 10000.0) / 100;
echo '%';

?>
</p>

<?php
$start_time = strtotime("5 December 2017, 20:46:10");
$now = time();
$ela = $now - $start_time;
$est = intval(1.0 * $ela / ($a - $start + 1) * ($end - $a - 1));
?>
<p>
<?php
echo "Elapsed: ";
echo intval($ela / (24 * 3600));
echo " day ";
echo intval($ela % (24 * 3600) / 3600);
echo " hour ";
echo intval($ela % 3600 / 60);
echo " min ";
echo intval($ela % 60);
echo " sec ";
?>
</p>

<p>
<?php
echo "Estimate: ";
echo intval($est / (24 * 3600));
echo " day ";
echo intval($est % (24 * 3600) / 3600);
echo " hour ";
echo intval($est % 3600 / 60);
echo " min ";
echo intval($est % 60);
echo " sec ";
?>
</p>

<p>
Fail URLs: <br/>
<?php
$t = file_get_contents("/home/africamonkey/Downloads/oeis/fail.txt");
$t = trim($t);
$t = str_replace("\r\n", "<br>", $t);
$t = str_replace("\n", "<br>", $t);
echo $t;
?>
</p>

<!--
<h2>120.77.154.199</h2>
<h3>85000-97000</h3>
<?php echo file_get_contents('http://120.77.154.199:8080'); ?>
-->



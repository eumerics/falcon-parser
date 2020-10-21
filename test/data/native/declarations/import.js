import 'a'; //? <+#>
import * as a from 'a'; //? <+#>
import a from 'a'; //? <+#>
import {} from 'a'; //? <+#>
import {a} from 'a'; //? <+#>
import {a as b} from 'a'; //? <+#>
import a, * as b from 'a'; //? <+#>
import a, {b, c as d, e,} from 'a'; //? <+#>
import('a'); ///? <+#>

/// lexical uniqueness of import declarations
import a from 'a'; var a; //? <-#>
import a from 'a'; let a; //? <-#>
import a from 'a'; { var a; } //? <-#>
import a from 'a'; { let a; } //? <+#>
import * as a from 'a'; var a; //? <-#>
import * as a from 'a'; let a; //? <-#>
import * as a from 'a'; { var a; } //? <-#>
import * as a from 'a'; { let a; } //? <+#>
import {a} from 'a'; var a; //? <-#>
import {a} from 'a'; let a; //? <-#>
import {a} from 'a'; { var a; } //? <-#>
import {a} from 'a'; { let a; } //? <+#>
import {a as b} from 'a'; var b; //? <-#>
import {a as b} from 'a'; let b; //? <-#>
import {a as b} from 'a'; { var b; } //? <-#>
import {a as b} from 'a'; { let b; } //? <+#>

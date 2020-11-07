import 'a'; //? <+#>
import * as a from 'a'; //? <+#>
import a from 'a'; //? <+#>
import {} from 'a'; //? <+#>
import {a} from 'a'; //? <+#>
import {a as b} from 'a'; //? <+#>
import a, * as b from 'a'; //? <+#>
import a, {b, c as d, e,} from 'a'; //? <+#>
import('a'); //? <+#>

import; //? <-#> @1:7 -missing_import_specifier

/// lexical uniqueness of import declarations
//- duplicate_symbol
import a from 'a'; var a; //? <-#> @1:24
import a from 'a'; let a; //? <-#> @1:24
import a from 'a'; { var a; } //? <-#> @1:26
import a from 'a'; { let a; } //? <+#>
import * as a from 'a'; var a; //? <-#> @1:29
import * as a from 'a'; let a; //? <-#> @1:29
import * as a from 'a'; { var a; } //? <-#> @1:31
import * as a from 'a'; { let a; } //? <+#>
import {a} from 'a'; var a; //? <-#> @1:26
import {a} from 'a'; let a; //? <-#> @1:26
import {a} from 'a'; { var a; } //? <-#> @1:28
import {a} from 'a'; { let a; } //? <+#>
import {a as b} from 'a'; var b; //? <-#> @1:31
import {a as b} from 'a'; let b; //? <-#> @1:31
import {a as b} from 'a'; { var b; } //? <-#> @1:33
import {a as b} from 'a'; { let b; } //? <+#>

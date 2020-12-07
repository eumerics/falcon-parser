import as from ''; //? <+#>
import {as} from ''; //? <+#>
import {as as as} from ''; //? <+#>
export * as as from ''; //? <+#>
export {as} from ''; //? <+#>
export {as as as} from ''; //? <+#>

!{ async async(){ async; } }; //? <+>
async async => async; //? <+>
async (async) => async; //? <+>
async function async(){ async; } //? <+>
class async { async async(){ async; }} //? <+>
!async function async(){ async; } //? <+>
!class async { async async(){ async; }} //? <+>
/// 'async extends async' is not a compile time error but is a runtime error
class async extends async { async async(){ async; }} //? <+>
!class async extends async { async async(){ async; }} //? <+>

import from from ''; //? <+#>

!{ get get(){} }; //? <+>
class get { get get(){} } //? <+>
!class get { get get(){} }; //? <+>

!{ set set(set){} }; //? <+>
class set { set set(set){} } //? <+>
!class set { set set(set){} }; //? <+>

for(of of of); //? <+>

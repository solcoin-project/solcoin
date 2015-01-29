Solcoin [![Build Status](https://travis-ci.org/solcoin-project/solcoin.svg?branch=master)](https://travis-ci.org/solcoin-project/solcoin)
=======

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2011-2015 Litecoin Developers
Copyright (c) 2014-     Solcoin Developers

http://www.solcoin.net/


Technical details
-----------------

Solcoin is a variant of Bitcoin using scrypt as proof-of-work algorithm. It was inspired by Mooncoin, and is based on the Litecoin source code.

 - 1772 coins per block
 - subsidy is halved every 131072nd block (every 40 weeks) until
   a permanent floor of 27 coins is reached, which should happen
   circa 4.5 years after launch
 - no hard limit on total amount of coins; effective amount of
   coins in circulation should stabilize around 696 million
 - initial network difficulty of 0.125, and 2 blocks pre-mined
   as a measure towards reducing risk of instantaneous forking
 - 3.14 minute block target
 - employs the Kimoto Gravity Well to adjust network difficulty
   in order to avoid pool-hopping side effects


License
-------

Solcoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.


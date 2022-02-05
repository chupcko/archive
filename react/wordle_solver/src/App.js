import { useContext, useEffect } from 'react';

import { Divider } from '@mui/material';

import { StoreContext } from './Store';

import Solver from './Solver';
import Checker from './Checker';

const App = (props) => {

  const { init } = useContext(StoreContext);

  useEffect(
    () => {
      init(false);
    },
    []
  );

  return (
    <>
      <Solver />
      <Divider sx={ { padding: 1 } } />
      <Checker />
    </>
  );

};

export default App;

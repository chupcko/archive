import { render } from 'react-dom';

import { createTheme, ThemeProvider } from '@mui/material/styles';
import { teal, blue, red } from '@mui/material/colors';

import { StoreProvider } from './Store';

import App from './App';

const theme = createTheme(
  {
    palette: {
      primary: {
        main: teal[500]
      },
      secondary: {
        main: blue[500]
      },
      error: {
        main: red[500]
      }
    },
  }
);

render(
  <StoreProvider>
    <App />
  </StoreProvider>,
  document.querySelector('#root')
);
